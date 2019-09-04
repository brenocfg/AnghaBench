#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_oid ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_fromraw (TYPE_1__*,unsigned char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void test_object_raw_compare__succeed_on_copy_oid(void)
{
	git_oid a, b;
	unsigned char exp[] = {
		0x16, 0xa6, 0x77, 0x70, 0xb7,
		0xd8, 0xd7, 0x23, 0x17, 0xc4,
		0xb7, 0x75, 0x21, 0x3c, 0x23,
		0xa8, 0xbd, 0x74, 0xf5, 0xe0,
	};
	memset(&b, 0, sizeof(b));
	git_oid_fromraw(&a, exp);
	git_oid_cpy(&b, &a);
	cl_git_pass(memcmp(a.id, exp, sizeof(a.id)));
}