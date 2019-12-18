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
struct archive_entry {int /*<<< orphan*/  archive; int /*<<< orphan*/  acl; } ;
typedef  int /*<<< orphan*/  la_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/ * archive_acl_to_text_w (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

wchar_t *
archive_entry_acl_to_text_w(struct archive_entry *entry, la_ssize_t *len,
    int flags)
{
	return (archive_acl_to_text_w(&entry->acl, len, flags,
	    entry->archive));
}