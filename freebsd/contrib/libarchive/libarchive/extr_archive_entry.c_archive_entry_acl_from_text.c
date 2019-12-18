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

/* Variables and functions */
 int archive_acl_from_text_l (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 

int
archive_entry_acl_from_text(struct archive_entry *entry,
    const char *text, int type)
{
	return (archive_acl_from_text_l(&entry->acl, text, type, NULL));
}