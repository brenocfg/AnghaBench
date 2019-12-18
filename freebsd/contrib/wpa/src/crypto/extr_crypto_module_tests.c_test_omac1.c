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
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/ * omac1_test_vectors ; 
 scalar_t__ test_omac1_vector (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int test_omac1(void)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(omac1_test_vectors); i++) {
		if (test_omac1_vector(&omac1_test_vectors[i], i))
			return 1;
	}

	wpa_printf(MSG_INFO, "OMAC1-AES-128 test cases passed");

	return 0;
}