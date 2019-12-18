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
typedef  scalar_t__ uint32_t ;
struct utmpx {scalar_t__ ut_type; } ;

/* Variables and functions */
 int SNMP_ERR_NOERROR ; 
 scalar_t__ USER_PROCESS ; 
 int /*<<< orphan*/  endutxent () ; 
 struct utmpx* getutxent () ; 
 int /*<<< orphan*/  setutxent () ; 

__attribute__((used)) static int
OS_getSystemNumUsers(uint32_t *nu)
{
	struct utmpx *utmp;

	setutxent();
	*nu = 0;
	while ((utmp = getutxent()) != NULL) {
		if (utmp->ut_type == USER_PROCESS)
			(*nu)++;
	}
	endutxent();

	return (SNMP_ERR_NOERROR);
}