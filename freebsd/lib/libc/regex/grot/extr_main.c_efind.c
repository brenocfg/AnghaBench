#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* re_endp; } ;
typedef  TYPE_1__ regex_t ;
typedef  int /*<<< orphan*/  efbuf ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ATOI ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  regerror (int /*<<< orphan*/ ,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
efind(char *name)
{
	static char efbuf[100];
	size_t n;
	regex_t re;

	sprintf(efbuf, "REG_%s", name);
	assert(strlen(efbuf) < sizeof(efbuf));
	re.re_endp = efbuf;
	(void) regerror(REG_ATOI, &re, efbuf, sizeof(efbuf));
	return(atoi(efbuf));
}