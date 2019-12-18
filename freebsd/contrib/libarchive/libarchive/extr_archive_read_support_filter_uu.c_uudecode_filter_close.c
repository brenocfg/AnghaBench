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
struct uudecode {struct uudecode* out_buff; struct uudecode* in_buff; } ;
struct archive_read_filter {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct uudecode*) ; 

__attribute__((used)) static int
uudecode_filter_close(struct archive_read_filter *self)
{
	struct uudecode *uudecode;

	uudecode = (struct uudecode *)self->data;
	free(uudecode->in_buff);
	free(uudecode->out_buff);
	free(uudecode);

	return (ARCHIVE_OK);
}