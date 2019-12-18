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
struct TYPE_3__ {scalar_t__ floating; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ FLOATING_AUTO_ON ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

bool con_is_floating(Con *con) {
    assert(con != NULL);
    return (con->floating >= FLOATING_AUTO_ON);
}