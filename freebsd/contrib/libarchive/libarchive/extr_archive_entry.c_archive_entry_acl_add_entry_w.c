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
typedef  int /*<<< orphan*/  wchar_t ;
struct archive_entry {int /*<<< orphan*/  acl; } ;

/* Variables and functions */
 int archive_acl_add_entry_w_len (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/  const*) ; 

int
archive_entry_acl_add_entry_w(struct archive_entry *entry,
    int type, int permset, int tag, int id, const wchar_t *name)
{
	return archive_acl_add_entry_w_len(&entry->acl,
	    type, permset, tag, id, name, wcslen(name));
}