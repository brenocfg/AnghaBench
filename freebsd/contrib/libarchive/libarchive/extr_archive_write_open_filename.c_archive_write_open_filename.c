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
 int archive_write_open_fd (struct archive*,int) ; 
 int open_filename (struct archive*,int,char const*) ; 

int
archive_write_open_filename(struct archive *a, const char *filename)
{

	if (filename == NULL || filename[0] == '\0')
		return (archive_write_open_fd(a, 1));

	return (open_filename(a, 1, filename));
}