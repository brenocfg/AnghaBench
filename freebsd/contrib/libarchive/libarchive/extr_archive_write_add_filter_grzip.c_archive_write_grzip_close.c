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
struct write_grzip {int /*<<< orphan*/  pdata; } ;
struct archive_write_filter {scalar_t__ data; } ;

/* Variables and functions */
 int __archive_write_program_close (struct archive_write_filter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
archive_write_grzip_close(struct archive_write_filter *f)
{
	struct write_grzip *data = (struct write_grzip *)f->data;

	return __archive_write_program_close(f, data->pdata);
}