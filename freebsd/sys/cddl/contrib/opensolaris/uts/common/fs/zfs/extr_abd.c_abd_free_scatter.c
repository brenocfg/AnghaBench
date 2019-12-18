#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * abd_chunks; } ;
struct TYPE_8__ {TYPE_1__ abd_scatter; } ;
struct TYPE_9__ {size_t abd_size; int /*<<< orphan*/  abd_children; TYPE_2__ abd_u; } ;
typedef  TYPE_3__ abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABDSTAT_BUMPDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ABDSTAT_INCR (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  abd_free_chunk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_free_struct (TYPE_3__*) ; 
 size_t abd_scatter_chunkcnt (TYPE_3__*) ; 
 int /*<<< orphan*/  abdstat_scatter_chunk_waste ; 
 int /*<<< orphan*/  abdstat_scatter_cnt ; 
 int /*<<< orphan*/  abdstat_scatter_data_size ; 
 size_t zfs_abd_chunk_size ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
abd_free_scatter(abd_t *abd)
{
	size_t n = abd_scatter_chunkcnt(abd);
	for (int i = 0; i < n; i++) {
		abd_free_chunk(abd->abd_u.abd_scatter.abd_chunks[i]);
	}

	zfs_refcount_destroy(&abd->abd_children);
	ABDSTAT_BUMPDOWN(abdstat_scatter_cnt);
	ABDSTAT_INCR(abdstat_scatter_data_size, -(int)abd->abd_size);
	ABDSTAT_INCR(abdstat_scatter_chunk_waste,
	    abd->abd_size - n * zfs_abd_chunk_size);

	abd_free_struct(abd);
}