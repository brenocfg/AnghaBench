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
 int archive_acl_add_entry (int /*<<< orphan*/ *,int,int,int,int,char const*) ; 

int
archive_entry_acl_add_entry(struct archive_entry *entry,
    int type, int permset, int tag, int id, const char *name)
{
	return archive_acl_add_entry(&entry->acl, type, permset, tag, id, name);
}