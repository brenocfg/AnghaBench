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
struct archive_entry {int /*<<< orphan*/  ae_symlink_type; struct archive* archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_SYMLINK_TYPE_UNDEFINED ; 
 scalar_t__ calloc (int,int) ; 

struct archive_entry *
archive_entry_new2(struct archive *a)
{
	struct archive_entry *entry;

	entry = (struct archive_entry *)calloc(1, sizeof(*entry));
	if (entry == NULL)
		return (NULL);
	entry->archive = a;
	entry->ae_symlink_type = AE_SYMLINK_TYPE_UNDEFINED;
	return (entry);
}