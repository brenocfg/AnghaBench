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
struct archive_acl {int dummy; } ;
struct archive_entry {struct archive_acl acl; } ;

/* Variables and functions */

struct archive_acl *
archive_entry_acl(struct archive_entry *entry)
{
	return &entry->acl;
}