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
struct thread {int /*<<< orphan*/ * td_retval; } ;
struct modfind_args {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/ * module_t ;

/* Variables and functions */
 int ENOENT ; 
 int MAXMODNAME ; 
 int /*<<< orphan*/  MOD_SLOCK ; 
 int /*<<< orphan*/  MOD_SUNLOCK ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_getid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * module_lookupbyname (char*) ; 

int
sys_modfind(struct thread *td, struct modfind_args *uap)
{
	int error = 0;
	char name[MAXMODNAME];
	module_t mod;

	if ((error = copyinstr(uap->name, name, sizeof name, 0)) != 0)
		return (error);

	MOD_SLOCK;
	mod = module_lookupbyname(name);
	if (mod == NULL)
		error = ENOENT;
	else
		td->td_retval[0] = module_getid(mod);
	MOD_SUNLOCK;
	return (error);
}