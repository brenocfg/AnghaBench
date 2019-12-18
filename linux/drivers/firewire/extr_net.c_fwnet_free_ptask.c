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
struct fwnet_packet_task {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwnet_packet_task_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fwnet_packet_task*) ; 

__attribute__((used)) static void fwnet_free_ptask(struct fwnet_packet_task *ptask)
{
	dev_kfree_skb_any(ptask->skb);
	kmem_cache_free(fwnet_packet_task_cache, ptask);
}