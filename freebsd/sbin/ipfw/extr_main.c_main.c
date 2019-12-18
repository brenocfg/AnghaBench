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

/* Variables and functions */
 int EX_OK ; 
 int /*<<< orphan*/  EX_USAGE ; 
 unsigned short MAKEWORD (int,int) ; 
 int /*<<< orphan*/  R_OK ; 
 int WSAStartup (unsigned short,int /*<<< orphan*/ *) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ipfw_main (int,char**) ; 
 int /*<<< orphan*/  ipfw_readfile (int,char**) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
main(int ac, char *av[])
{
#if defined(_WIN32) && defined(TCC)
	{
		WSADATA wsaData;
		int ret=0;
		unsigned short wVersionRequested = MAKEWORD(2, 2);
		ret = WSAStartup(wVersionRequested, &wsaData);
		if (ret != 0) {
			/* Tell the user that we could not find a usable */
			/* Winsock DLL.				  */
			printf("WSAStartup failed with error: %d\n", ret);
			return 1;
		}
	}
#endif
	/*
	 * If the last argument is an absolute pathname, interpret it
	 * as a file to be preprocessed.
	 */

	if (ac > 1 && av[ac - 1][0] == '/') {
		if (access(av[ac - 1], R_OK) == 0)
			ipfw_readfile(ac, av);
		else
			err(EX_USAGE, "pathname: %s", av[ac - 1]);
	} else {
		if (ipfw_main(ac, av)) {
			errx(EX_USAGE,
			    "usage: ipfw [options]\n"
			    "do \"ipfw -h\" or \"man ipfw\" for details");
		}
	}
	return EX_OK;
}