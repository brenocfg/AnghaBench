#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; scalar_t__ (* check_prot ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  app_data ; 
 int code ; 
 char* level_to_name (int) ; 
 TYPE_1__* mech ; 
 int name_to_level (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sec_complete ; 
 int /*<<< orphan*/  sec_status () ; 
 scalar_t__ set_command_prot (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 

void
sec_prot_command(int argc, char **argv)
{
    int level;

    if(argc > 2)
	goto usage;

    if(!sec_complete) {
	printf("No security data exchange has taken place.\n");
	code = -1;
	return;
    }

    if(argc == 1) {
	sec_status();
    } else {
	level = name_to_level(argv[1]);
	if(level == -1)
	    goto usage;

	if((*mech->check_prot)(app_data, level)) {
	    printf("%s does not implement %s protection.\n",
		   mech->name, level_to_name(level));
	    code = -1;
	    return;
	}
	if(set_command_prot(level) < 0) {
	    code = -1;
	    return;
	}
    }
    code = 0;
    return;
 usage:
    printf("usage: %s [clear|safe|confidential|private]\n",
	   argv[0]);
    code = -1;
}