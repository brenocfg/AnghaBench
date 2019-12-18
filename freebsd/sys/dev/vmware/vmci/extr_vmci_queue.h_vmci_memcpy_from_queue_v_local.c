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
struct vmci_queue {int dummy; } ;

/* Variables and functions */
 int vmci_memcpy_from_queue_v (void*,size_t,struct vmci_queue const*,int /*<<< orphan*/ ,size_t,int,int) ; 

__attribute__((used)) static inline int
vmci_memcpy_from_queue_v_local(void *dest, size_t dest_offset,
    const struct vmci_queue *queue, uint64_t queue_offset, size_t size,
    int buf_type, bool can_block)
{

	return (vmci_memcpy_from_queue_v(dest, dest_offset, queue, queue_offset,
	    size, buf_type, can_block));
}