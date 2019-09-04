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
struct repository {int dummy; } ;
struct diff_filespec {int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 scalar_t__ diff_populate_filespec (struct repository*,struct diff_filespec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diff_filespec_is_identical(struct repository *r,
				      struct diff_filespec *one,
				      struct diff_filespec *two)
{
	if (S_ISGITLINK(one->mode))
		return 0;
	if (diff_populate_filespec(r, one, 0))
		return 0;
	if (diff_populate_filespec(r, two, 0))
		return 0;
	return !memcmp(one->data, two->data, one->size);
}