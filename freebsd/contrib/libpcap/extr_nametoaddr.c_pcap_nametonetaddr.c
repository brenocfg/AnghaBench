#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct netent_data {int dummy; } ;
struct netent {int /*<<< orphan*/  n_net; } ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;

/* Variables and functions */
 struct netent* getnetbyname (char const*) ; 
 int getnetbyname_r (char const*,struct netent*,char*,...) ; 

bpf_u_int32
pcap_nametonetaddr(const char *name)
{
#ifdef _WIN32
	/*
	 * There's no "getnetbyname()" on Windows.
	 *
	 * XXX - I guess we could use the BSD code to read
	 * C:\Windows\System32\drivers\etc/networks, assuming
	 * that's its home on all the versions of Windows
	 * we use, but that file probably just has the loopback
	 * network on 127/24 on 99 44/100% of Windows machines.
	 *
	 * (Heck, these days it probably just has that on 99 44/100%
	 * of *UN*X* machines.)
	 */
	return 0;
#else
	/*
	 * UN*X.
	 */
	struct netent *np;
  #if defined(HAVE_LINUX_GETNETBYNAME_R)
	/*
	 * We have Linux's reentrant getnetbyname_r().
	 */
	struct netent result_buf;
	char buf[1024];	/* arbitrary size */
	int h_errnoval;
	int err;

	err = getnetbyname_r(name, &result_buf, buf, sizeof buf, &np,
	    &h_errnoval);
	if (err != 0) {
		/*
		 * XXX - dynamically allocate the buffer, and make it
		 * bigger if we get ERANGE back?
		 */
		return 0;
	}
  #elif defined(HAVE_SOLARIS_IRIX_GETNETBYNAME_R)
	/*
	 * We have Solaris's and IRIX's reentrant getnetbyname_r().
	 */
	struct netent result_buf;
	char buf[1024];	/* arbitrary size */

	np = getnetbyname_r(name, &result_buf, buf, (int)sizeof buf);
  #elif defined(HAVE_AIX_GETNETBYNAME_R)
	/*
	 * We have AIX's reentrant getnetbyname_r().
	 */
	struct netent result_buf;
	struct netent_data net_data;

	if (getnetbyname_r(name, &result_buf, &net_data) == -1)
		np = NULL;
	else
		np = &result_buf;
  #else
 	/*
 	 * We don't have any getnetbyname_r(); either we have a
 	 * getnetbyname() that uses thread-specific data, in which
 	 * case we're thread-safe (sufficiently recent FreeBSD,
 	 * sufficiently recent Darwin-based OS, sufficiently recent
 	 * HP-UX, sufficiently recent Tru64 UNIX), or we have the
 	 * traditional getnetbyname() (everything else, including
 	 * current NetBSD and OpenBSD), in which case we're not
 	 * thread-safe.
 	 */
	np = getnetbyname(name);
  #endif
	if (np != NULL)
		return np->n_net;
	else
		return 0;
#endif /* _WIN32 */
}