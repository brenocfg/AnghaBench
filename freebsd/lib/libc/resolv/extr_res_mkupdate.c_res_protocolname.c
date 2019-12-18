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
struct valuelist {int dummy; } ;
struct protoent {char const* p_name; } ;

/* Variables and functions */
 struct protoent* cgetprotobynumber (int) ; 
 struct valuelist* protolist ; 
 int /*<<< orphan*/  res_buildprotolist () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
res_protocolname(int num) {
	static char number[8];
	struct protoent *pp;

	if (protolist == (struct valuelist *)0)
		res_buildprotolist();
	pp = cgetprotobynumber(num);
	if (pp == NULL)  {
		(void) sprintf(number, "%d", num);
		return (number);
	}
	return (pp->p_name);
}