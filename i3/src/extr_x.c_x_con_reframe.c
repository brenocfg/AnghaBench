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
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  _x_con_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x_con_init (int /*<<< orphan*/ *) ; 

void x_con_reframe(Con *con) {
    _x_con_kill(con);
    x_con_init(con);
}