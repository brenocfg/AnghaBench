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
struct sf_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sched_unpin () ; 
 int /*<<< orphan*/  sf_buf_free (struct sf_buf*) ; 

void
dmar_unmap_pgtbl(struct sf_buf *sf)
{

	sf_buf_free(sf);
	sched_unpin();
}