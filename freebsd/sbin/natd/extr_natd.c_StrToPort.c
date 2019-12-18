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
typedef  int /*<<< orphan*/  u_short ;
struct servent {int /*<<< orphan*/  s_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char const*,char const*) ; 
 struct servent* getservbyname (char const*,char const*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtol (char const*,char**,int) ; 

u_short StrToPort (const char* str, const char* proto)
{
	u_short		port;
	struct servent*	sp;
	char*		end;

	port = strtol (str, &end, 10);
	if (end != str)
		return htons (port);

	sp = getservbyname (str, proto);
	if (!sp)
		errx (1, "%s/%s: unknown service", str, proto);

	return sp->s_port;
}