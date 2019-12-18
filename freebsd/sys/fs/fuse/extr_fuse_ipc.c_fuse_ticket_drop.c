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
struct fuse_ticket {int /*<<< orphan*/  tk_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  fticket_destroy (struct fuse_ticket*) ; 
 int refcount_release (int /*<<< orphan*/ *) ; 

int
fuse_ticket_drop(struct fuse_ticket *ftick)
{
	int die;

	die = refcount_release(&ftick->tk_refcount);
	if (die)
		fticket_destroy(ftick);

	return die;
}