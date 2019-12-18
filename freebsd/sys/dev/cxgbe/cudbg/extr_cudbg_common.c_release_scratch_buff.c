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
struct cudbg_buffer {scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

void release_scratch_buff(struct cudbg_buffer *pscratch_buff,
			  struct cudbg_buffer *pdbg_buff)
{
	pdbg_buff->size += pscratch_buff->size;
	/* Reset the used buffer to zero.
 	 * If we dont do this, then it will effect the ext entity logic.
 	 */
	memset(pscratch_buff->data, 0, pscratch_buff->size);
	pscratch_buff->data = NULL;
	pscratch_buff->offset = 0;
	pscratch_buff->size = 0;
}