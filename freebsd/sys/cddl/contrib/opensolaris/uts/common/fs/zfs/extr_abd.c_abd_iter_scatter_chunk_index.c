#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct abd_iter {size_t iter_pos; TYPE_3__* iter_abd; } ;
struct TYPE_4__ {size_t abd_offset; } ;
struct TYPE_5__ {TYPE_1__ abd_scatter; } ;
struct TYPE_6__ {TYPE_2__ abd_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  abd_is_linear (TYPE_3__*) ; 
 size_t zfs_abd_chunk_size ; 

__attribute__((used)) static inline size_t
abd_iter_scatter_chunk_index(struct abd_iter *aiter)
{
	ASSERT(!abd_is_linear(aiter->iter_abd));
	return ((aiter->iter_abd->abd_u.abd_scatter.abd_offset +
	    aiter->iter_pos) / zfs_abd_chunk_size);
}