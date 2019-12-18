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
struct archive {int dummy; } ;

/* Variables and functions */
 int archive_read_open_filenames (struct archive*,char const**,size_t) ; 

int
archive_read_open_filename(struct archive *a, const char *filename,
    size_t block_size)
{
	const char *filenames[2];
	filenames[0] = filename;
	filenames[1] = NULL;
	return archive_read_open_filenames(a, filenames, block_size);
}