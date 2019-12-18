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

/* Variables and functions */
 int /*<<< orphan*/  HV_GRP_NCS ; 
 int /*<<< orphan*/  sun4v_hvapi_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void n2_spu_hvapi_unregister(void)
{
	sun4v_hvapi_unregister(HV_GRP_NCS);
}