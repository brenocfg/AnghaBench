#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct skcipher_walk_buffer {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {scalar_t__ nbytes; int flags; scalar_t__ stride; int /*<<< orphan*/ * page; TYPE_4__ dst; TYPE_2__ src; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ PAGE_SIZE ; 
 int SKCIPHER_WALK_PHYS ; 
 struct skcipher_walk_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ offset_in_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_map_src (struct skcipher_walk*) ; 
 int /*<<< orphan*/  skcipher_queue_write (struct skcipher_walk*,struct skcipher_walk_buffer*) ; 
 int /*<<< orphan*/  skcipher_unmap_src (struct skcipher_walk*) ; 
 int /*<<< orphan*/  skcipher_walk_gfp (struct skcipher_walk*) ; 

__attribute__((used)) static int skcipher_next_copy(struct skcipher_walk *walk)
{
	struct skcipher_walk_buffer *p;
	u8 *tmp = walk->page;

	skcipher_map_src(walk);
	memcpy(tmp, walk->src.virt.addr, walk->nbytes);
	skcipher_unmap_src(walk);

	walk->src.virt.addr = tmp;
	walk->dst.virt.addr = tmp;

	if (!(walk->flags & SKCIPHER_WALK_PHYS))
		return 0;

	p = kmalloc(sizeof(*p), skcipher_walk_gfp(walk));
	if (!p)
		return -ENOMEM;

	p->data = walk->page;
	p->len = walk->nbytes;
	skcipher_queue_write(walk, p);

	if (offset_in_page(walk->page) + walk->nbytes + walk->stride >
	    PAGE_SIZE)
		walk->page = NULL;
	else
		walk->page += walk->nbytes;

	return 0;
}