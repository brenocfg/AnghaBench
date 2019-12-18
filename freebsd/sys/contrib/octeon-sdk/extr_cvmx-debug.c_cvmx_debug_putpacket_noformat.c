#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* putpacket ) (char*) ;} ;
struct TYPE_3__ {size_t comm_type; } ;

/* Variables and functions */
 TYPE_2__** cvmx_debug_comms ; 
 TYPE_1__* cvmx_debug_globals ; 
 int /*<<< orphan*/  cvmx_debug_printf (char*,char*) ; 
 int stub1 (char*) ; 

__attribute__((used)) static int cvmx_debug_putpacket_noformat(char *packet)
{
    if (cvmx_debug_comms[cvmx_debug_globals->comm_type]->putpacket == NULL)
        return 0;
    cvmx_debug_printf("Reply: %s\n", packet);
    return cvmx_debug_comms[cvmx_debug_globals->comm_type]->putpacket(packet);
}