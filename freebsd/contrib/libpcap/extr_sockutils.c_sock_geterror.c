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

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  sock_fmterror (char const*,int /*<<< orphan*/ ,char*,int) ; 

void sock_geterror(const char *caller, char *errbuf, int errbuflen)
{
#ifdef _WIN32
	if (errbuf == NULL)
		return;
	sock_fmterror(caller, GetLastError(), errbuf, errbuflen);
#else
	if (errbuf == NULL)
		return;
	sock_fmterror(caller, errno, errbuf, errbuflen);
#endif
}