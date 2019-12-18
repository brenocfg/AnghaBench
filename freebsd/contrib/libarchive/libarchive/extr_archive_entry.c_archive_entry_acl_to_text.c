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
struct archive_entry {int /*<<< orphan*/  acl; } ;
typedef  int /*<<< orphan*/  la_ssize_t ;

/* Variables and functions */
 char* archive_acl_to_text_l (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

char *
archive_entry_acl_to_text(struct archive_entry *entry, la_ssize_t *len,
    int flags)
{
	return (archive_acl_to_text_l(&entry->acl, len, flags, NULL));
}