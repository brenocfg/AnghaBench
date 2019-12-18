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
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 int LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 int snprintf (char*,int,char*,...) ; 
 char* stoa (int /*<<< orphan*/  const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

const char *
hostnameaddr(
	const char *		hostname,
	const sockaddr_u *	addr
	)
{
	const char *	addrtxt;
	char *		result;
	int		cnt;

	addrtxt = stoa(addr);
	LIB_GETBUF(result);
	if (strcmp(hostname, addrtxt))
		cnt = snprintf(result, LIB_BUFLENGTH, "%s %s",
			       hostname, addrtxt);
	else
		cnt = snprintf(result, LIB_BUFLENGTH, "%s", addrtxt);
	if (cnt >= LIB_BUFLENGTH)
		snprintf(result, LIB_BUFLENGTH,
			 "hostnameaddr ERROR have %d (%d needed)",
			 LIB_BUFLENGTH, cnt + 1);

	return result;
}