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

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  enable_ioat_test (int) ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 char* kern_getenv (char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

void
ioat_test_attach(void)
{
	char *val;

	val = kern_getenv("hw.ioat.enable_ioat_test");
	if (val != NULL && strcmp(val, "0") != 0) {
		mtx_lock(&Giant);
		enable_ioat_test(true);
		mtx_unlock(&Giant);
	}
	freeenv(val);
}