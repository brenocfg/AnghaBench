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
struct v7tar {int dummy; } ;
struct archive_write {int /*<<< orphan*/ * format_data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct v7tar*) ; 

__attribute__((used)) static int
archive_write_v7tar_free(struct archive_write *a)
{
	struct v7tar *v7tar;

	v7tar = (struct v7tar *)a->format_data;
	free(v7tar);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}