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
struct abd_iter {scalar_t__ iter_mapsize; int /*<<< orphan*/ * iter_mapaddr; scalar_t__ iter_pos; int /*<<< orphan*/ * iter_abd; } ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_verify (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
abd_iter_init(struct abd_iter *aiter, abd_t *abd)
{
	abd_verify(abd);
	aiter->iter_abd = abd;
	aiter->iter_pos = 0;
	aiter->iter_mapaddr = NULL;
	aiter->iter_mapsize = 0;
}