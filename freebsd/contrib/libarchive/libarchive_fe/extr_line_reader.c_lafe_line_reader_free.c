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
struct lafe_line_reader {struct lafe_line_reader* pathname; struct lafe_line_reader* buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct lafe_line_reader*) ; 

void
lafe_line_reader_free(struct lafe_line_reader *lr)
{
	free(lr->buff);
	free(lr->pathname);
	free(lr);
}