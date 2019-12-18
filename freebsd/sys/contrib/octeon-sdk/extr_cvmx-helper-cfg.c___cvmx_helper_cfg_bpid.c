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
struct TYPE_2__ {int ccpp_bpid; } ;

/* Variables and functions */
 TYPE_1__** cvmx_cfg_port ; 

int __cvmx_helper_cfg_bpid(int interface, int index)
{
    return cvmx_cfg_port[interface][index].ccpp_bpid;
}