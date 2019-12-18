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
struct archive {scalar_t__ read_data_offset; int /*<<< orphan*/ * read_data_block; scalar_t__ read_data_requested; scalar_t__ read_data_is_posix_read; scalar_t__ read_data_remaining; scalar_t__ read_data_output_offset; } ;

/* Variables and functions */

void __archive_reset_read_data(struct archive * a)
{
	a->read_data_output_offset = 0;
	a->read_data_remaining = 0;
	a->read_data_is_posix_read = 0;
	a->read_data_requested = 0;

   /* extra resets, from rar.c */
   a->read_data_block = NULL;
   a->read_data_offset = 0;
}