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
struct TYPE_3__ {char* app_name; scalar_t__ valid; scalar_t__ hotplug_activated_coremask; scalar_t__ coremask; } ;
typedef  TYPE_1__ cvmx_app_hotplug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,unsigned int,unsigned int,unsigned int) ; 

void print_hot_plug_info(cvmx_app_hotplug_info_t* hpinfo)
{
    printf("name=%s coremask=%08x hotplugged coremask=%08x valid=%d\n", hpinfo->app_name,
           (unsigned int)hpinfo->coremask, (unsigned int)hpinfo->hotplug_activated_coremask, (unsigned int)hpinfo->valid);
}