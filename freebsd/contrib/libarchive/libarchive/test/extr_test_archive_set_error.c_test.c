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
 int /*<<< orphan*/  archive_errno (struct archive*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int,char*,char const*) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test(struct archive *a, int code, const char *msg)
{
	archive_set_error(a, code, "%s", msg);

	assertEqualInt(code, archive_errno(a));
	assertEqualString(msg, archive_error_string(a));
}