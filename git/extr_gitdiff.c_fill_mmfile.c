#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct repository {int dummy; } ;
struct diff_filespec {char* data; scalar_t__ size; } ;
struct TYPE_3__ {char* ptr; scalar_t__ size; } ;
typedef  TYPE_1__ mmfile_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FILE_VALID (struct diff_filespec*) ; 
 scalar_t__ diff_populate_filespec (struct repository*,struct diff_filespec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_mmfile(struct repository *r, mmfile_t *mf,
		       struct diff_filespec *one)
{
	if (!DIFF_FILE_VALID(one)) {
		mf->ptr = (char *)""; /* does not matter */
		mf->size = 0;
		return 0;
	}
	else if (diff_populate_filespec(r, one, 0))
		return -1;

	mf->ptr = one->data;
	mf->size = one->size;
	return 0;
}