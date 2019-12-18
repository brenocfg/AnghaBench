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
struct pstore_record {int /*<<< orphan*/ * buf; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFIVARS_DATA_SIZE_MAX ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  efi_pstore_sysfs_entry_iter (struct pstore_record*) ; 
 scalar_t__ efivar_entry_iter_begin () ; 
 int /*<<< orphan*/  efivar_entry_iter_end () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t efi_pstore_read(struct pstore_record *record)
{
	ssize_t size;

	record->buf = kzalloc(EFIVARS_DATA_SIZE_MAX, GFP_KERNEL);
	if (!record->buf)
		return -ENOMEM;

	if (efivar_entry_iter_begin()) {
		size = -EINTR;
		goto out;
	}
	size = efi_pstore_sysfs_entry_iter(record);
	efivar_entry_iter_end();

out:
	if (size <= 0) {
		kfree(record->buf);
		record->buf = NULL;
	}
	return size;
}