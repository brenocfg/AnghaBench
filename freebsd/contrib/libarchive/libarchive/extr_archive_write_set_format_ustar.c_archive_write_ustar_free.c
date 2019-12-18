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
struct ustar {int dummy; } ;
struct archive_write {int /*<<< orphan*/ * format_data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct ustar*) ; 

__attribute__((used)) static int
archive_write_ustar_free(struct archive_write *a)
{
	struct ustar *ustar;

	ustar = (struct ustar *)a->format_data;
	free(ustar);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}