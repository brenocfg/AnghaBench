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
struct sf_buffer {unsigned long* sdbt; int num_sdbt; unsigned long* tail; scalar_t__ num_sdb; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  free_sampling_buffer (struct sf_buffer*) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int realloc_sampling_buffer (struct sf_buffer*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfdbg ; 

__attribute__((used)) static int alloc_sampling_buffer(struct sf_buffer *sfb, unsigned long num_sdb)
{
	int rc;

	if (sfb->sdbt)
		return -EINVAL;

	/* Allocate the sample-data-block-table origin */
	sfb->sdbt = (unsigned long *) get_zeroed_page(GFP_KERNEL);
	if (!sfb->sdbt)
		return -ENOMEM;
	sfb->num_sdb = 0;
	sfb->num_sdbt = 1;

	/* Link the table origin to point to itself to prepare for
	 * realloc_sampling_buffer() invocation.
	 */
	sfb->tail = sfb->sdbt;
	*sfb->tail = (unsigned long)(void *) sfb->sdbt + 1;

	/* Allocate requested number of sample-data-blocks */
	rc = realloc_sampling_buffer(sfb, num_sdb, GFP_KERNEL);
	if (rc) {
		free_sampling_buffer(sfb);
		debug_sprintf_event(sfdbg, 4, "alloc_sampling_buffer: "
			"realloc_sampling_buffer failed with rc=%i\n", rc);
	} else
		debug_sprintf_event(sfdbg, 4,
			"alloc_sampling_buffer: tear=%p dear=%p\n",
			sfb->sdbt, (void *) *sfb->sdbt);
	return rc;
}