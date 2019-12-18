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
struct warc_s {int dummy; } ;
struct archive_write {struct warc_s* format_data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct warc_s*) ; 

__attribute__((used)) static int
_warc_free(struct archive_write *a)
{
	struct warc_s *w = a->format_data;

	free(w);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}