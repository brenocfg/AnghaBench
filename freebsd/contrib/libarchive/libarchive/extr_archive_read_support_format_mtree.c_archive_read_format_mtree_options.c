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
struct mtree {int checkfs; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
archive_read_format_mtree_options(struct archive_read *a,
    const char *key, const char *val)
{
	struct mtree *mtree;

	mtree = (struct mtree *)(a->format->data);
	if (strcmp(key, "checkfs")  == 0) {
		/* Allows to read information missing from the mtree from the file system */
		if (val == NULL || val[0] == 0) {
			mtree->checkfs = 0;
		} else {
			mtree->checkfs = 1;
		}
		return (ARCHIVE_OK);
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}