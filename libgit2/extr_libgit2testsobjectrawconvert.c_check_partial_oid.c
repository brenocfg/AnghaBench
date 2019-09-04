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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  git_oid_nfmt (char*,size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void check_partial_oid(
	char *buffer, size_t count, const git_oid *oid, const char *expected)
{
	git_oid_nfmt(buffer, count, oid);
	buffer[count] = '\0';
	cl_assert_equal_s(expected, buffer);
}