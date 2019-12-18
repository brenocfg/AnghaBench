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
struct diff_filepair {int /*<<< orphan*/  two; int /*<<< orphan*/  one; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct diff_filepair*) ; 
 int /*<<< orphan*/  free_filespec (int /*<<< orphan*/ ) ; 

void diff_free_filepair(struct diff_filepair *p)
{
	free_filespec(p->one);
	free_filespec(p->two);
	free(p);
}