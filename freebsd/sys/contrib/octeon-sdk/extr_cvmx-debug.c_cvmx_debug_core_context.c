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
typedef  int /*<<< orphan*/  cvmx_debug_core_context_t ;
struct TYPE_2__ {int /*<<< orphan*/  volatile* contextes; } ;

/* Variables and functions */
 TYPE_1__* cvmx_debug_globals ; 
 size_t cvmx_get_core_num () ; 

__attribute__((used)) static volatile cvmx_debug_core_context_t *cvmx_debug_core_context(void)
{
    return &cvmx_debug_globals->contextes[cvmx_get_core_num()];
}