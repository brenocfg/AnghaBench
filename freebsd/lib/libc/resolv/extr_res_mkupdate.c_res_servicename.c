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
typedef  int u_int16_t ;
struct valuelist {int dummy; } ;
struct servent {char const* s_name; } ;

/* Variables and functions */
 struct servent* cgetservbyport (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  res_buildservicelist () ; 
 struct valuelist* servicelist ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
res_servicename(u_int16_t port, const char *proto) {	/*%< Host byte order. */
	static char number[8];
	struct servent *ss;

	if (servicelist == (struct valuelist *)0)
		res_buildservicelist();
	ss = cgetservbyport(htons(port), proto);
	if (ss == NULL)  {
		(void) sprintf(number, "%d", port);
		return (number);
	}
	return (ss->s_name);
}