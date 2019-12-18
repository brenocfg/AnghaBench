#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* parent; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  floating_head; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floating_windows ; 

void floating_raise_con(Con *con) {
    DLOG("Raising floating con %p / %s\n", con, con->name);
    TAILQ_REMOVE(&(con->parent->floating_head), con, floating_windows);
    TAILQ_INSERT_TAIL(&(con->parent->floating_head), con, floating_windows);
}