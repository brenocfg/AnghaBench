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
struct TYPE_2__ {int (* to_lookup_symbol ) (char*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 TYPE_1__ debug_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int stub1 (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
debug_to_lookup_symbol (char *name, CORE_ADDR *addrp)
{
  int retval;

  retval = debug_target.to_lookup_symbol (name, addrp);

  fprintf_unfiltered (gdb_stdlog, "target_lookup_symbol (%s, xxx)\n", name);

  return retval;
}