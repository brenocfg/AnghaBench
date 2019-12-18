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
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smiInit (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

int
nd_init(char *errbuf, size_t errbuf_size)
{
#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	/*
	 * Request Winsock 2.2; we expect Winsock 2.
	 */
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		strlcpy(errbuf, "Attempting to initialize Winsock failed",
		    errbuf_size);
		return (-1);
	}
#endif /* _WIN32 */

#ifdef USE_LIBSMI
	/*
	 * XXX - should we just fail if this fails?  Some of the
	 * libsmi calls may fail.
	 */
	smiInit("tcpdump");
#endif

	/*
	 * Clears the error buffer, and uses it so we don't get
	 * "unused argument" warnings at compile time.
	 */
	strlcpy(errbuf, "", errbuf_size);
	return (0);
}