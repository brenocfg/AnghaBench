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
struct sshbuf {int /*<<< orphan*/  refcount; struct sshbuf* parent; } ;

/* Variables and functions */
 int sshbuf_check_sanity (struct sshbuf*) ; 

int
sshbuf_set_parent(struct sshbuf *child, struct sshbuf *parent)
{
	int r;

	if ((r = sshbuf_check_sanity(child)) != 0 ||
	    (r = sshbuf_check_sanity(parent)) != 0)
		return r;
	child->parent = parent;
	child->parent->refcount++;
	return 0;
}