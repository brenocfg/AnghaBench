#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  u_long ;
struct proc_handle {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  pr_mapname; } ;
typedef  TYPE_1__ prmap_t ;
struct TYPE_9__ {scalar_t__ st_value; } ;
typedef  TYPE_2__ GElf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_EQ_MSG (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_STOP ; 
 int /*<<< orphan*/  REG_PC ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcmp (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_1__* proc_addr2map (struct proc_handle*,int /*<<< orphan*/ ) ; 
 int proc_addr2sym (struct proc_handle*,int /*<<< orphan*/ ,char*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  proc_bkptregadj (int /*<<< orphan*/ *) ; 
 int proc_regget (struct proc_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_wstatus (struct proc_handle*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  target_prog_file ; 

__attribute__((used)) static void
verify_bkpt(struct proc_handle *phdl, GElf_Sym *sym, const char *symname,
    const char *mapname)
{
	char *name, *mapname_copy, *mapbname;
	GElf_Sym tsym;
	prmap_t *map;
	size_t namesz;
	u_long addr;
	int error, state;

	state = proc_wstatus(phdl);
	ATF_REQUIRE_EQ_MSG(state, PS_STOP, "process has state %d", state);

	/* Get the program counter and decrement it. */
	error = proc_regget(phdl, REG_PC, &addr);
	ATF_REQUIRE_EQ_MSG(error, 0, "failed to obtain PC for '%s'",
	    target_prog_file);
	proc_bkptregadj(&addr);

	/*
	 * Make sure the PC matches the expected value obtained from the symbol
	 * definition we looked up earlier.
	 */
	ATF_CHECK_EQ_MSG(addr, sym->st_value,
	    "program counter 0x%lx doesn't match expected value 0x%jx",
	    addr, (uintmax_t)sym->st_value);

	/*
	 * Ensure we can look up the r_debug_state symbol using its starting
	 * address and that the resulting symbol matches the one we found using
	 * a name lookup.
	 */
	namesz = strlen(symname) + 1;
	name = malloc(namesz);
	ATF_REQUIRE(name != NULL);

	error = proc_addr2sym(phdl, addr, name, namesz, &tsym);
	ATF_REQUIRE_EQ_MSG(error, 0, "failed to look up symbol at 0x%lx", addr);
	ATF_REQUIRE_EQ(memcmp(sym, &tsym, sizeof(*sym)), 0);
	ATF_REQUIRE_EQ(strcmp(symname, name), 0);
	free(name);

	map = proc_addr2map(phdl, addr);
	ATF_REQUIRE_MSG(map != NULL, "failed to look up map for address 0x%lx",
	    addr);
	mapname_copy = strdup(map->pr_mapname);
	mapbname = basename(mapname_copy);
	ATF_REQUIRE_EQ_MSG(strcmp(mapname, mapbname), 0,
	    "expected map name '%s' doesn't match '%s'", mapname, mapbname);
	free(mapname_copy);
}