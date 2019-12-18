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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swcr_id ; 

__attribute__((used)) static int
swcr_detach(device_t dev)
{
	crypto_unregister_all(swcr_id);
	return 0;
}