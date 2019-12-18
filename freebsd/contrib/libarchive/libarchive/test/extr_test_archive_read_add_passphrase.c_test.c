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
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_FAILED ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_read_add_passphrase (struct archive*,char*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test(int pristine)
{
	struct archive* a = archive_read_new();

	if (!pristine) {
		archive_read_support_filter_all(a);
		archive_read_support_format_all(a);
        }

	assertEqualInt(ARCHIVE_OK, archive_read_add_passphrase(a, "pass1"));
	/* An empty passphrase cannot be accepted. */
	assertEqualInt(ARCHIVE_FAILED, archive_read_add_passphrase(a, ""));
	/* NULL passphrases cannot be accepted. */
	assertEqualInt(ARCHIVE_FAILED, archive_read_add_passphrase(a, NULL));

	archive_read_free(a);
}