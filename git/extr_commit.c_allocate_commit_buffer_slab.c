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
struct buffer_slab {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_buffer_slab (struct buffer_slab*) ; 
 struct buffer_slab* xmalloc (int) ; 

struct buffer_slab *allocate_commit_buffer_slab(void)
{
	struct buffer_slab *bs = xmalloc(sizeof(*bs));
	init_buffer_slab(bs);
	return bs;
}