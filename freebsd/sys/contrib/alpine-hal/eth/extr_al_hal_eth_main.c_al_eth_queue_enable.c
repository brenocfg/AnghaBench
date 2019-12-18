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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_hal_eth_adapter {int dummy; } ;
typedef  enum al_udma_type { ____Placeholder_al_udma_type } al_udma_type ;

/* Variables and functions */
 int EPERM ; 

int al_eth_queue_enable(struct al_hal_eth_adapter *adapter __attribute__((__unused__)),
			enum al_udma_type type __attribute__((__unused__)),
			uint32_t qid __attribute__((__unused__)))
{
	return -EPERM;
}