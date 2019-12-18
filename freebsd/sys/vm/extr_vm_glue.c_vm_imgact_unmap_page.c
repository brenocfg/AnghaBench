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
typedef  int /*<<< orphan*/  vm_page_t ;
struct sf_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQ_ACTIVE ; 
 int /*<<< orphan*/  sched_unpin () ; 
 int /*<<< orphan*/  sf_buf_free (struct sf_buf*) ; 
 int /*<<< orphan*/  sf_buf_page (struct sf_buf*) ; 
 int /*<<< orphan*/  vm_page_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_imgact_unmap_page(struct sf_buf *sf)
{
	vm_page_t m;

	m = sf_buf_page(sf);
	sf_buf_free(sf);
	sched_unpin();
	vm_page_unwire(m, PQ_ACTIVE);
}