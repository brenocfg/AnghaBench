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
struct archive_read {TYPE_1__* extract; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ad; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int archive_write_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static int
archive_read_extract_cleanup(struct archive_read *a)
{
	int ret = ARCHIVE_OK;

	if (a->extract->ad != NULL) {
		ret = archive_write_free(a->extract->ad);
	}
	free(a->extract);
	a->extract = NULL;
	return (ret);
}