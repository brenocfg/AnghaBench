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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  POP_BANK ; 
 int /*<<< orphan*/  PUSH_BANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SceneCameraAtDest_b () ; 
 int /*<<< orphan*/  scene_bank ; 

UBYTE SceneCameraAtDest()
{
  UBYTE at_dest;
  PUSH_BANK(scene_bank);
  at_dest = SceneCameraAtDest_b();
  POP_BANK;
  return at_dest;
}