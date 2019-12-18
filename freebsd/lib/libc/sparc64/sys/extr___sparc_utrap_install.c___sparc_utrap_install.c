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
typedef  void* utrap_handler_t ;
typedef  int /*<<< orphan*/  utrap_entry_t ;
struct sparc_utrap_install_args {int num; struct sparc_utrap_args* handlers; } ;
struct sparc_utrap_args {void** old_precise; void** old_deferred; void* new_deferred; void* new_precise; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPARC_UTRAP_INSTALL ; 
 int sysarch (int /*<<< orphan*/ ,struct sparc_utrap_install_args*) ; 

int
__sparc_utrap_install(utrap_entry_t type, utrap_handler_t new_precise,
    utrap_handler_t new_deferred, utrap_handler_t *old_precise,
    utrap_handler_t *old_deferred)
{
	struct sparc_utrap_install_args uia;
	struct sparc_utrap_args ua[1];

	ua[0].type = type;
	ua[0].new_precise = new_precise;
	ua[0].new_deferred = new_deferred;
	ua[0].old_precise = old_precise;
	ua[0].old_deferred = old_deferred;
	uia.num = 1;
	uia.handlers = ua;
	return (sysarch(SPARC_UTRAP_INSTALL, &uia));
}