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
struct rs6000_framedata {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  skip_prologue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rs6000_framedata*) ; 

__attribute__((used)) static CORE_ADDR
rs6000_skip_prologue (CORE_ADDR pc)
{
  struct rs6000_framedata frame;
  pc = skip_prologue (pc, 0, &frame);
  return pc;
}