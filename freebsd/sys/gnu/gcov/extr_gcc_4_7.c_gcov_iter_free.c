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
struct gcov_iterator {struct gcov_iterator* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GCOV ; 
 int /*<<< orphan*/  free (struct gcov_iterator*,int /*<<< orphan*/ ) ; 

void
gcov_iter_free(struct gcov_iterator *iter)
{
	free(iter->buffer, M_GCOV);
	free(iter, M_GCOV);
}