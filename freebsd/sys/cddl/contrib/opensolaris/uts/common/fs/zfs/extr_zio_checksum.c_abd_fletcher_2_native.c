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
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_iterate_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fletcher_2_incremental_native ; 
 int /*<<< orphan*/  fletcher_init (int /*<<< orphan*/ *) ; 

void
abd_fletcher_2_native(abd_t *abd, uint64_t size,
    const void *ctx_template, zio_cksum_t *zcp)
{
	fletcher_init(zcp);
	(void) abd_iterate_func(abd, 0, size,
	    fletcher_2_incremental_native, zcp);
}