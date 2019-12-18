#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct bytecode {struct bytecode* parent; } ;
struct TYPE_3__ {struct bytecode* compiled; } ;
typedef  TYPE_1__ inst ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t nesting_level(struct bytecode* bc, inst* target) {
  uint16_t level = 0;
  assert(bc && target && target->compiled);
  while (bc && target->compiled != bc) {
    level++;
    bc = bc->parent;
  }
  assert(bc && bc == target->compiled);
  return level;
}