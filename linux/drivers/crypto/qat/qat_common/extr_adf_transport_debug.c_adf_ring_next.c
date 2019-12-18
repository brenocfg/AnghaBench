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
struct seq_file {struct adf_etr_ring_data* private; } ;
struct adf_etr_ring_data {void* base_addr; int /*<<< orphan*/  msg_size; int /*<<< orphan*/  ring_size; } ;
typedef  int loff_t ;

/* Variables and functions */
 int ADF_MSG_SIZE_TO_BYTES (int /*<<< orphan*/ ) ; 
 int ADF_SIZE_TO_RING_SIZE_IN_BYTES (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *adf_ring_next(struct seq_file *sfile, void *v, loff_t *pos)
{
	struct adf_etr_ring_data *ring = sfile->private;

	if (*pos >= (ADF_SIZE_TO_RING_SIZE_IN_BYTES(ring->ring_size) /
		     ADF_MSG_SIZE_TO_BYTES(ring->msg_size)))
		return NULL;

	return ring->base_addr +
		(ADF_MSG_SIZE_TO_BYTES(ring->msg_size) * (*pos)++);
}