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
struct datalink {unsigned int state; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  datalink_State (struct datalink*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,...) ; 
 int /*<<< orphan*/ * states ; 

__attribute__((used)) static void
datalink_NewState(struct datalink *dl, unsigned state)
{
  if (state != dl->state) {
    if (state < sizeof states / sizeof states[0]) {
      log_Printf(LogPHASE, "%s: %s -> %s\n", dl->name, datalink_State(dl),
                 states[state]);
      dl->state = state;
    } else
      log_Printf(LogERROR, "%s: Can't enter state %d !\n", dl->name, state);
  }
}