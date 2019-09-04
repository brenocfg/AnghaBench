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
typedef  void git_cert ;

/* Variables and functions */
 int GIT_ECERTIFICATE ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cert_check_assert_invalid(git_cert *cert, int valid, const char* host, void *payload)
{
	GIT_UNUSED(cert); GIT_UNUSED(host); GIT_UNUSED(payload);

	cl_assert_equal_i(0, valid);

	return GIT_ECERTIFICATE;
}