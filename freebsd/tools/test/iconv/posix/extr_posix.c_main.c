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
 int /*<<< orphan*/  close_1 ; 
 int /*<<< orphan*/  conv_2big ; 
 int /*<<< orphan*/  conv_ebadf ; 
 int /*<<< orphan*/  conv_eilseq ; 
 int /*<<< orphan*/  conv_einval ; 
 int /*<<< orphan*/  conv_ret ; 
 int /*<<< orphan*/  open_1 ; 
 int /*<<< orphan*/  open_2 ; 
 int /*<<< orphan*/  test (int /*<<< orphan*/ ,char*) ; 

int
main(void)
{

	test(open_1, "open_1");
	test(open_2, "open_2");
	test(close_1, "close_1");
	test(conv_ret, "conv_ret");
	test(conv_ebadf, "conv_ebadf");
	test(conv_2big, "conv_2big");
	test(conv_einval, "conv_einval");
	test(conv_eilseq, "conv_eilseq");
}