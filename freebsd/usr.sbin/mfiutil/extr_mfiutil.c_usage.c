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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	fprintf(stderr, "usage: mfiutil [-de] [-u unit] <command> ...\n\n");
	fprintf(stderr, "Commands include:\n");
	fprintf(stderr, "    version\n");
	fprintf(stderr, "    show adapter              - display controller information\n");
	fprintf(stderr, "    show battery              - display battery information\n");
	fprintf(stderr, "    show config               - display RAID configuration\n");
	fprintf(stderr, "    show drives               - list physical drives\n");
	fprintf(stderr, "    show events               - display event log\n");
	fprintf(stderr, "    show firmware             - list firmware images\n");
	fprintf(stderr, "    show foreign              - display detected foreign volumes\n");
	fprintf(stderr, "    show logstate             - display event log sequence numbers\n");
	fprintf(stderr, "    show volumes              - list logical volumes\n");
	fprintf(stderr, "    show patrol               - display patrol read status\n");
	fprintf(stderr, "    show progress             - display status of active operations\n");
	fprintf(stderr, "    fail <drive>              - fail a physical drive\n");
	fprintf(stderr, "    good <drive>              - set a failed/SYSPD drive as UNCONFIGURED\n");
	fprintf(stderr, "    rebuild <drive>           - mark failed drive ready for rebuild\n");
	fprintf(stderr, "    syspd <drive>             - set drive into use as SYSPD JBOD\n");
	fprintf(stderr, "    drive progress <drive>    - display status of active operations\n");
	fprintf(stderr, "    drive clear <drive> <start|stop> - clear a drive with all 0x00\n");
	fprintf(stderr, "    start rebuild <drive>\n");
	fprintf(stderr, "    abort rebuild <drive>\n");
	fprintf(stderr, "    locate <drive> <on|off>   - toggle drive LED\n");
	fprintf(stderr, "    cache <volume> [command [setting]]\n");
	fprintf(stderr, "    name <volume> <name>\n");
	fprintf(stderr, "    volume progress <volume>  - display status of active operations\n");
	fprintf(stderr, "    clear                     - clear volume configuration\n");
	fprintf(stderr, "    create <type> [-v] [-s stripe_size] <drive>[,<drive>[,...]] [<drive>[,<drive>[,...]]\n");
	fprintf(stderr, "    delete <volume>\n");
	fprintf(stderr, "    add <drive> [volume]      - add a hot spare\n");
	fprintf(stderr, "    remove <drive>            - remove a hot spare\n");
	fprintf(stderr, "    patrol <disable|auto|manual> [interval [start]]\n");
	fprintf(stderr, "    start patrol              - start a patrol read\n");
	fprintf(stderr, "    stop patrol               - stop a patrol read\n");
	fprintf(stderr, "    foreign scan              - scan for foreign configurations\n");
	fprintf(stderr, "    foreign clear [volume]    - clear foreign configurations (default all)\n");
	fprintf(stderr, "    foreign diag [volume]     - diagnostic display foreign configurations (default all)\n");
	fprintf(stderr, "    foreign preview [volume]  - preview foreign configurations (default all)\n");
	fprintf(stderr, "    foreign import [volume]   - import foreign configurations (default all)\n");
	fprintf(stderr, "    flash <firmware>\n");
	fprintf(stderr, "    start learn               - start a BBU relearn\n");
	fprintf(stderr, "    bbu <setting> <value>     - set BBU properties\n");
	fprintf(stderr, "    ctrlprop rebuild [rate]   - get/set the volume rebuild rate\n");
	fprintf(stderr, "    ctrlprop alarm [0/1]      - enable/disable controller alarms\n");
#ifdef DEBUG
	fprintf(stderr, "    debug                     - debug 'show config'\n");
	fprintf(stderr, "    dump                      - display 'saved' config\n");
#endif
	exit(1);
}