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
struct fifolog_file {scalar_t__ fd; int /*<<< orphan*/ * recbuf; int /*<<< orphan*/ * zs; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
fifolog_int_close(struct fifolog_file **ff)
{
	struct fifolog_file *f;

	f = *ff;
	*ff = NULL;
	if (f == NULL)
		return;

	if (f->fd >= 0)
		(void)close(f->fd);
	if (f->zs != NULL)
		free(f->zs);
	if (f->recbuf != NULL)
		free(f->recbuf);
}