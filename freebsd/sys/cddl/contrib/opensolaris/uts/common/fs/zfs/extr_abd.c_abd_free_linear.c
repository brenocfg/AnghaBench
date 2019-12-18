#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  abd_buf; } ;
struct TYPE_7__ {TYPE_1__ abd_linear; } ;
struct TYPE_8__ {int abd_flags; scalar_t__ abd_size; int /*<<< orphan*/  abd_children; TYPE_2__ abd_u; } ;
typedef  TYPE_3__ abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABDSTAT_BUMPDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ABDSTAT_INCR (int /*<<< orphan*/ ,int) ; 
 int ABD_FLAG_META ; 
 int /*<<< orphan*/  abd_free_struct (TYPE_3__*) ; 
 int /*<<< orphan*/  abdstat_linear_cnt ; 
 int /*<<< orphan*/  abdstat_linear_data_size ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_buf_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zio_data_buf_free (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
abd_free_linear(abd_t *abd)
{
	if (abd->abd_flags & ABD_FLAG_META) {
		zio_buf_free(abd->abd_u.abd_linear.abd_buf, abd->abd_size);
	} else {
		zio_data_buf_free(abd->abd_u.abd_linear.abd_buf, abd->abd_size);
	}

	zfs_refcount_destroy(&abd->abd_children);
	ABDSTAT_BUMPDOWN(abdstat_linear_cnt);
	ABDSTAT_INCR(abdstat_linear_data_size, -(int)abd->abd_size);

	abd_free_struct(abd);
}