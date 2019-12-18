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
struct TYPE_2__ {char const* acl_text; } ;
struct archive_entry {TYPE_1__ acl; } ;

/* Variables and functions */
 char const* archive_acl_to_text_l (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ archive_entry_acl_text_compat (int*) ; 
 int /*<<< orphan*/  free (char const*) ; 

const char *
archive_entry_acl_text(struct archive_entry *entry, int flags)
{
	free(entry->acl.acl_text);
	entry->acl.acl_text = NULL;
	if (archive_entry_acl_text_compat(&flags) == 0)
		entry->acl.acl_text = archive_acl_to_text_l(&entry->acl, NULL,
		    flags, NULL);

	return (entry->acl.acl_text);
}