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
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_vars ; 
 int /*<<< orphan*/  ptype_command ; 
 int /*<<< orphan*/  whatis_command ; 

void
_initialize_typeprint (void)
{

  add_com ("ptype", class_vars, ptype_command,
	   "Print definition of type TYPE.\n\
Argument may be a type name defined by typedef, or \"struct STRUCT-TAG\"\n\
or \"class CLASS-NAME\" or \"union UNION-TAG\" or \"enum ENUM-TAG\".\n\
The selected stack frame's lexical context is used to look up the name.");

  add_com ("whatis", class_vars, whatis_command,
	   "Print data type of expression EXP.");

}