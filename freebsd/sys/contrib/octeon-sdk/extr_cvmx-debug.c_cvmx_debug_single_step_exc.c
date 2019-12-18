#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ddbl; int /*<<< orphan*/  ddbs; int /*<<< orphan*/  dbp; int /*<<< orphan*/  dib; scalar_t__ dss; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_debug_register_t ;

/* Variables and functions */

__attribute__((used)) static int cvmx_debug_single_step_exc(cvmx_debug_register_t *debug_reg)
{
    if (debug_reg->s.dss && !debug_reg->s.dib && !debug_reg->s.dbp && !debug_reg->s.ddbs && !debug_reg->s.ddbl)
        return 1;
    return 0;
}