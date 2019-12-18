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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ dev_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  cav_unregister_algs () ; 
 TYPE_1__ dev_handle ; 

void cvm_crypto_exit(void)
{
	u32 dev_count;

	dev_count = --dev_handle.dev_count;
	if (!dev_count)
		cav_unregister_algs();
}