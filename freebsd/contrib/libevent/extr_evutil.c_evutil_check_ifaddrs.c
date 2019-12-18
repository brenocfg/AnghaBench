#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct ifaddrs {struct sockaddr* ifa_addr; struct ifaddrs* ifa_next; } ;
typedef  scalar_t__ ULONG ;
struct TYPE_9__ {TYPE_2__* FirstUnicastAddress; struct TYPE_9__* Next; } ;
struct TYPE_7__ {struct sockaddr* lpSockaddr; } ;
struct TYPE_8__ {TYPE_1__ Address; struct TYPE_8__* Next; } ;
typedef  TYPE_2__ IP_ADAPTER_UNICAST_ADDRESS ;
typedef  TYPE_3__ IP_ADAPTER_ADDRESSES ;
typedef  scalar_t__ HMODULE ;
typedef  scalar_t__ (* GetAdaptersAddresses_fn_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,scalar_t__*) ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 scalar_t__ ERROR_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  FLAGS ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 scalar_t__ GetProcAddress (scalar_t__,char*) ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  event_warn (char*) ; 
 int /*<<< orphan*/  evutil_found_ifaddr (struct sockaddr*) ; 
 scalar_t__ evutil_load_windows_system_library_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 scalar_t__ getifaddrs (struct ifaddrs**) ; 
 int /*<<< orphan*/  mm_free (TYPE_3__*) ; 
 TYPE_3__* mm_malloc (scalar_t__) ; 

__attribute__((used)) static int
evutil_check_ifaddrs(void)
{
#if defined(EVENT__HAVE_GETIFADDRS)
	/* Most free Unixy systems provide getifaddrs, which gives us a linked list
	 * of struct ifaddrs. */
	struct ifaddrs *ifa = NULL;
	const struct ifaddrs *i;
	if (getifaddrs(&ifa) < 0) {
		event_warn("Unable to call getifaddrs()");
		return -1;
	}

	for (i = ifa; i; i = i->ifa_next) {
		if (!i->ifa_addr)
			continue;
		evutil_found_ifaddr(i->ifa_addr);
	}

	freeifaddrs(ifa);
	return 0;
#elif defined(_WIN32)
	/* Windows XP began to provide GetAdaptersAddresses. Windows 2000 had a
	   "GetAdaptersInfo", but that's deprecated; let's just try
	   GetAdaptersAddresses and fall back to connect+getsockname.
	*/
	HMODULE lib = evutil_load_windows_system_library_(TEXT("ihplapi.dll"));
	GetAdaptersAddresses_fn_t fn;
	ULONG size, res;
	IP_ADAPTER_ADDRESSES *addresses = NULL, *address;
	int result = -1;

#define FLAGS (GAA_FLAG_SKIP_ANYCAST | \
               GAA_FLAG_SKIP_MULTICAST | \
               GAA_FLAG_SKIP_DNS_SERVER)

	if (!lib)
		goto done;

	if (!(fn = (GetAdaptersAddresses_fn_t) GetProcAddress(lib, "GetAdaptersAddresses")))
		goto done;

	/* Guess how much space we need. */
	size = 15*1024;
	addresses = mm_malloc(size);
	if (!addresses)
		goto done;
	res = fn(AF_UNSPEC, FLAGS, NULL, addresses, &size);
	if (res == ERROR_BUFFER_OVERFLOW) {
		/* we didn't guess that we needed enough space; try again */
		mm_free(addresses);
		addresses = mm_malloc(size);
		if (!addresses)
			goto done;
		res = fn(AF_UNSPEC, FLAGS, NULL, addresses, &size);
	}
	if (res != NO_ERROR)
		goto done;

	for (address = addresses; address; address = address->Next) {
		IP_ADAPTER_UNICAST_ADDRESS *a;
		for (a = address->FirstUnicastAddress; a; a = a->Next) {
			/* Yes, it's a linked list inside a linked list */
			struct sockaddr *sa = a->Address.lpSockaddr;
			evutil_found_ifaddr(sa);
		}
	}

	result = 0;
done:
	if (lib)
		FreeLibrary(lib);
	if (addresses)
		mm_free(addresses);
	return result;
#else
	return -1;
#endif
}