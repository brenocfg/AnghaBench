#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ git_filebuf ;

/* Variables and functions */
 TYPE_1__ GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filebuf_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  git_filebuf_open (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 

void test_core_filebuf__4(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	char test[] = "test";

	cl_assert(file.buffer == NULL);

	cl_git_pass(git_filebuf_open(&file, test, 0, 0666));
	cl_assert(file.buffer != NULL);

	git_filebuf_cleanup(&file);
	cl_assert(file.buffer == NULL);
}