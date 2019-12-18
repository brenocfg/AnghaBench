#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_read {TYPE_1__* format; } ;
struct ar {struct ar* strtab; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct ar*) ; 

__attribute__((used)) static int
archive_read_format_ar_cleanup(struct archive_read *a)
{
	struct ar *ar;

	ar = (struct ar *)(a->format->data);
	free(ar->strtab);
	free(ar);
	(a->format->data) = NULL;
	return (ARCHIVE_OK);
}