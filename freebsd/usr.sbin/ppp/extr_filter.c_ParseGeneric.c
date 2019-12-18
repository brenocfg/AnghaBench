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
struct filterent {int /*<<< orphan*/  f_dstop; int /*<<< orphan*/  f_srcop; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  OP_NONE ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ParseGeneric(int argc, struct filterent *tgt)
{
  /*
   * Filter currently is a catch-all. Requests are either permitted or
   * dropped.
   */
  if (argc != 0) {
    log_Printf(LogWARN, "ParseGeneric: Too many parameters\n");
    return 0;
  } else
    tgt->f_srcop = tgt->f_dstop = OP_NONE;

  return 1;
}