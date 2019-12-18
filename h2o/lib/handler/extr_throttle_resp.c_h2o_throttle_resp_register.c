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
typedef  int /*<<< orphan*/  h2o_pathconf_t ;
struct TYPE_3__ {int /*<<< orphan*/  on_setup_ostream; } ;
typedef  TYPE_1__ h2o_filter_t ;

/* Variables and functions */
 TYPE_1__* h2o_create_filter (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  on_setup_ostream ; 

void h2o_throttle_resp_register(h2o_pathconf_t *pathconf)
{
    h2o_filter_t *self = h2o_create_filter(pathconf, sizeof(*self));
    self->on_setup_ostream = on_setup_ostream;
}