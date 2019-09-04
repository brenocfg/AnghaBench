#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  on_setup_ostream; } ;
struct st_server_timing_filter_t {int enforce; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  h2o_pathconf_t ;

/* Variables and functions */
 scalar_t__ h2o_create_filter (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  on_setup_ostream ; 

void h2o_server_timing_register(h2o_pathconf_t *pathconf, int enforce)
{
    struct st_server_timing_filter_t *self = (struct st_server_timing_filter_t *)h2o_create_filter(pathconf, sizeof(*self));
    self->super.on_setup_ostream = on_setup_ostream;
    self->enforce = enforce;
}