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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmci_queue {int /*<<< orphan*/  q_header; } ;

/* Variables and functions */
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  vmci_queue_header_add_consumer_head (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
vmci_queue_add_consumer_head(struct vmci_queue *queue,
    size_t add, uint64_t queue_size)
{

	vmci_queue_header_add_consumer_head(queue->q_header, add, queue_size);
	return (VMCI_SUCCESS);
}