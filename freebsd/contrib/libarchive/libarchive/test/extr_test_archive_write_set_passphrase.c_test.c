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
struct archive_write {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_FAILED ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  __archive_write_get_passphrase (struct archive_write*) ; 
 int /*<<< orphan*/  archive_write_add_filter_gzip (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 struct archive* archive_write_new () ; 
 int /*<<< orphan*/  archive_write_set_format_iso9660 (struct archive*) ; 
 int /*<<< orphan*/  archive_write_set_passphrase (struct archive*,char*) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test(int pristine)
{
	struct archive* a = archive_write_new();
	struct archive_write* aw = (struct archive_write *)a;

	if (!pristine) {
		archive_write_add_filter_gzip(a);
		archive_write_set_format_iso9660(a);
        }

	assertEqualInt(ARCHIVE_OK, archive_write_set_passphrase(a, "pass1"));
	/* An empty passphrase cannot be accepted. */
	assertEqualInt(ARCHIVE_FAILED, archive_write_set_passphrase(a, ""));
	/* NULL passphrases cannot be accepted. */
	assertEqualInt(ARCHIVE_FAILED, archive_write_set_passphrase(a, NULL));
	/* Check a passphrase. */
	assertEqualString("pass1", __archive_write_get_passphrase(aw));
	/* Change the passphrase. */
	assertEqualInt(ARCHIVE_OK, archive_write_set_passphrase(a, "pass2"));
	assertEqualString("pass2", __archive_write_get_passphrase(aw));

	archive_write_free(a);
}