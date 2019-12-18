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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct parsed_partitions {int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  gpt_header ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int read_lba (struct parsed_partitions*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static gpt_header *alloc_read_gpt_header(struct parsed_partitions *state,
					 u64 lba)
{
	gpt_header *gpt;
	unsigned ssz = bdev_logical_block_size(state->bdev);

	gpt = kmalloc(ssz, GFP_KERNEL);
	if (!gpt)
		return NULL;

	if (read_lba(state, lba, (u8 *) gpt, ssz) < ssz) {
		kfree(gpt);
                gpt=NULL;
		return NULL;
	}

	return gpt;
}