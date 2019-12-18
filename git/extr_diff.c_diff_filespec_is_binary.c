#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct repository {int /*<<< orphan*/  index; } ;
struct diff_filespec {int is_binary; int /*<<< orphan*/  size; scalar_t__ data; TYPE_1__* driver; } ;
struct TYPE_2__ {int binary; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_BINARY ; 
 scalar_t__ DIFF_FILE_VALID (struct diff_filespec*) ; 
 int buffer_is_binary (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_filespec_load_driver (struct diff_filespec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_populate_filespec (struct repository*,struct diff_filespec*,int /*<<< orphan*/ ) ; 

int diff_filespec_is_binary(struct repository *r,
			    struct diff_filespec *one)
{
	if (one->is_binary == -1) {
		diff_filespec_load_driver(one, r->index);
		if (one->driver->binary != -1)
			one->is_binary = one->driver->binary;
		else {
			if (!one->data && DIFF_FILE_VALID(one))
				diff_populate_filespec(r, one, CHECK_BINARY);
			if (one->is_binary == -1 && one->data)
				one->is_binary = buffer_is_binary(one->data,
						one->size);
			if (one->is_binary == -1)
				one->is_binary = 0;
		}
	}
	return one->is_binary;
}