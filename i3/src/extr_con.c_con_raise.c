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
 int /*<<< orphan*/ * con_inside_floating (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  floating_raise_con (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void con_raise(Con *con) {
    Con *floating = con_inside_floating(con);
    if (floating) {
        floating_raise_con(floating);
    }
}