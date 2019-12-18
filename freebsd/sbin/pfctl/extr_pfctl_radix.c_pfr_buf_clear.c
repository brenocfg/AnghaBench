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
struct pfr_buffer {scalar_t__ pfrb_msize; scalar_t__ pfrb_size; int /*<<< orphan*/ * pfrb_caddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
pfr_buf_clear(struct pfr_buffer *b)
{
	if (b == NULL)
		return;
	if (b->pfrb_caddr != NULL)
		free(b->pfrb_caddr);
	b->pfrb_caddr = NULL;
	b->pfrb_size = b->pfrb_msize = 0;
}