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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ibmp ; 
 int mad_register_server_via (int,int /*<<< orphan*/ ,long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mad_register_server(int mgmt, uint8_t rmpp_version,
			long method_mask[], uint32_t class_oui)
{
	return mad_register_server_via(mgmt, rmpp_version, method_mask,
				       class_oui, ibmp);
}