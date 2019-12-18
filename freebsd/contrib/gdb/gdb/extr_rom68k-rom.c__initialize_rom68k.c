#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* to_shortname; char* to_longname; char* to_doc; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_target (TYPE_1__*) ; 
 int /*<<< orphan*/  init_monitor_ops (TYPE_1__*) ; 
 int /*<<< orphan*/  init_rom68k_cmds () ; 
 int /*<<< orphan*/  rom68k_open ; 
 TYPE_1__ rom68k_ops ; 

void
_initialize_rom68k (void)
{
  init_rom68k_cmds ();
  init_monitor_ops (&rom68k_ops);

  rom68k_ops.to_shortname = "rom68k";
  rom68k_ops.to_longname = "Rom68k debug monitor for the IDP Eval board";
  rom68k_ops.to_doc = "Debug on a Motorola IDP eval board running the ROM68K monitor.\n\
Specify the serial device it is connected to (e.g. /dev/ttya).";
  rom68k_ops.to_open = rom68k_open;

  add_target (&rom68k_ops);
}