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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git__fromhex (unsigned int) ; 
 int /*<<< orphan*/  git_oid_fromstr (TYPE_1__*,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 

void test_object_raw_chars__find_invalid_chars_in_oid(void)
{
	git_oid out;
	unsigned char exp[] = {
		0x16, 0xa6, 0x77, 0x70, 0xb7,
		0xd8, 0xd7, 0x23, 0x17, 0xc4,
		0xb7, 0x75, 0x21, 0x3c, 0x23,
		0xa8, 0xbd, 0x74, 0xf5, 0xe0,
	};
	char in[] = "16a67770b7d8d72317c4b775213c23a8bd74f5e0";
	unsigned int i;

	for (i = 0; i < 256; i++) {
		in[38] = (char)i;
		if (git__fromhex(i) >= 0) {
			exp[19] = (unsigned char)(git__fromhex(i) << 4);
			cl_git_pass(git_oid_fromstr(&out, in));
			cl_assert(memcmp(out.id, exp, sizeof(out.id)) == 0);
		} else {
			cl_git_fail(git_oid_fromstr(&out, in));
		}
	}
}