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
typedef  int /*<<< orphan*/  vmem_t ;

/* Variables and functions */
 int /*<<< orphan*/ * bdomain ; 
 int buf_domains ; 
 scalar_t__ buf_recycle (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
bufkva_reclaim(vmem_t *vmem, int flags)
{
	bool done;
	int q;
	int i;

	done = false;
	for (i = 0; i < 5; i++) {
		for (q = 0; q < buf_domains; q++)
			if (buf_recycle(&bdomain[q], true) != 0)
				done = true;
		if (done)
			break;
	}
	return;
}