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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 scalar_t__ buf ; 
 scalar_t__ len ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,int /*<<< orphan*/  const*) ; 
 scalar_t__ wcslen (int /*<<< orphan*/  const*) ; 
 scalar_t__ wcsncmp (scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static void
assert_stream(const wchar_t *contents)
{
	if (wcslen(contents) != len)
		printf("bad length %zd for \"%ls\"\n", len, contents);
	else if (wcsncmp(buf, contents, wcslen(contents)) != 0)
		printf("bad buffer \"%ls\" for \"%ls\"\n", buf, contents);
}