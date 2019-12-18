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
typedef  int /*<<< orphan*/  mrdb_state ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  dbgcmd_state ;

/* Variables and functions */
 int /*<<< orphan*/  dbgcmd_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

dbgcmd_state
dbgcmd_eval(mrb_state *mrb, mrdb_state *mrdb)
{
  return dbgcmd_print(mrb, mrdb);
}