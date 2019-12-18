#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* cmd; char* resp_delim; char* term; char* term_cmd; } ;
struct TYPE_8__ {char* cmd; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * resp_delim; } ;
struct TYPE_7__ {char* cmdb; char* cmdw; char* cmdl; char* resp_delim; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * cmdll; } ;
struct TYPE_6__ {char* cmdb; char* cmdw; char* cmdl; int /*<<< orphan*/ * term_cmd; int /*<<< orphan*/ * term; int /*<<< orphan*/ * resp_delim; int /*<<< orphan*/ * cmdll; } ;
struct TYPE_10__ {char* cont; char* step; char* set_break; char* clr_break; char* clr_all_break; char* fill; char* dump_registers; char* register_pattern; char* load; char* loadresp; char* prompt; char* line_term; char* cmd_end; int /*<<< orphan*/  magic; int /*<<< orphan*/  regname; int /*<<< orphan*/ * regnames; int /*<<< orphan*/  stopbits; int /*<<< orphan*/ * target; int /*<<< orphan*/ * load_routine; int /*<<< orphan*/  supply_register; TYPE_4__ getreg; TYPE_3__ setreg; TYPE_2__ getmem; TYPE_1__ setmem; int /*<<< orphan*/ * stop; int /*<<< orphan*/  init; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_OPS_MAGIC ; 
 int /*<<< orphan*/  MO_PRINT_PROGRAM_OUTPUT ; 
 int /*<<< orphan*/  SERIAL_1_STOPBITS ; 
 TYPE_5__ rom68k_cmds ; 
 int /*<<< orphan*/  rom68k_inits ; 
 int /*<<< orphan*/  rom68k_ops ; 
 int /*<<< orphan*/  rom68k_regname ; 
 int /*<<< orphan*/  rom68k_supply_register ; 

__attribute__((used)) static void
init_rom68k_cmds (void)
{
  rom68k_cmds.flags = MO_PRINT_PROGRAM_OUTPUT;
  rom68k_cmds.init = rom68k_inits;	/* monitor init string */
  rom68k_cmds.cont = "go\r";
  rom68k_cmds.step = "st\r";
  rom68k_cmds.stop = NULL;
  rom68k_cmds.set_break = "db %x\r";
  rom68k_cmds.clr_break = "cb %x\r";
  rom68k_cmds.clr_all_break = "cb *\r";
  rom68k_cmds.fill = "fm %x %x %x\r";
  rom68k_cmds.setmem.cmdb = "pm %x %x\r";
  rom68k_cmds.setmem.cmdw = "pm.w %x %x\r";
  rom68k_cmds.setmem.cmdl = "pm.l %x %x\r";
  rom68k_cmds.setmem.cmdll = NULL;
  rom68k_cmds.setmem.resp_delim = NULL;
  rom68k_cmds.setmem.term = NULL;
  rom68k_cmds.setmem.term_cmd = NULL;
  rom68k_cmds.getmem.cmdb = "dm %x %x\r";
  rom68k_cmds.getmem.cmdw = "dm.w %x %x\r";
  rom68k_cmds.getmem.cmdl = "dm.l %x %x\r";
  rom68k_cmds.getmem.cmdll = NULL;
  rom68k_cmds.getmem.resp_delim = "  ";
  rom68k_cmds.getmem.term = NULL;
  rom68k_cmds.getmem.term_cmd = NULL;
  rom68k_cmds.setreg.cmd = "pr %s %x\r";
  rom68k_cmds.setreg.resp_delim = NULL;
  rom68k_cmds.setreg.term = NULL;
  rom68k_cmds.setreg.term_cmd = NULL;
  rom68k_cmds.getreg.cmd = "pr %s\r";
  rom68k_cmds.getreg.resp_delim = ":  ";
  rom68k_cmds.getreg.term = "= ";
  rom68k_cmds.getreg.term_cmd = ".\r";
  rom68k_cmds.dump_registers = "dr\r";
  rom68k_cmds.register_pattern =
    "\\(\\w+\\)=\\([0-9a-fA-F]+\\( +[0-9a-fA-F]+\\b\\)*\\)";
  rom68k_cmds.supply_register = rom68k_supply_register;
  rom68k_cmds.load_routine = NULL;
  rom68k_cmds.load = "dc\r";
  rom68k_cmds.loadresp = "Waiting for S-records from host... ";
  rom68k_cmds.prompt = "ROM68K :-> ";
  rom68k_cmds.line_term = "\r";
  rom68k_cmds.cmd_end = ".\r";
  rom68k_cmds.target = &rom68k_ops;
  rom68k_cmds.stopbits = SERIAL_1_STOPBITS;
  rom68k_cmds.regnames = NULL;
  rom68k_cmds.regname = rom68k_regname;
  rom68k_cmds.magic = MONITOR_OPS_MAGIC;
}