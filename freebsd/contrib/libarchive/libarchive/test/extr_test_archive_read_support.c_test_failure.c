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
typedef  int /*<<< orphan*/  (* enabler ) (struct archive*) ;
typedef  int /*<<< orphan*/  (* destructor ) (struct archive*) ;
typedef  struct archive* (* constructor ) () ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  archive_errno (struct archive*) ; 
 int /*<<< orphan*/ * archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_failure(constructor new_, enabler enable_, destructor free_)
{
	struct archive *a = new_();
	assertEqualIntA(a, ARCHIVE_FATAL, enable_(a));
	assert(NULL != archive_error_string(a));
	assertEqualIntA(a, -1, archive_errno(a));
	free_(a);
}