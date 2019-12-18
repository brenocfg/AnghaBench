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
struct mtree_writer {int classic; int output_global_set; } ;
struct archive_write {scalar_t__ format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int archive_write_set_format_mtree_default (struct archive*,char*) ; 

int
archive_write_set_format_mtree_classic(struct archive *_a)
{
	int r;

	r = archive_write_set_format_mtree_default(_a,
		"archive_write_set_format_mtree_classic");
	if (r == ARCHIVE_OK) {
		struct archive_write *a = (struct archive_write *)_a;
		struct mtree_writer *mtree;

		mtree = (struct mtree_writer *)a->format_data;

		/* Set to output a mtree archive in classic format. */
		mtree->classic = 1;
		/* Basically, mtree classic format uses '/set' global
		 * value. */
		mtree->output_global_set = 1;
	}
	return (r);
}