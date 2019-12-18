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
 int /*<<< orphan*/  ATF_CHECK (int) ; 
 int /*<<< orphan*/ * makebuf (size_t,int) ; 
 int wcslen (int /*<<< orphan*/  const*) ; 
 size_t wcsnlen (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wmemcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void
test_wcsnlen(const wchar_t *s)
{
	wchar_t *s1;
	size_t size, len, bufsize;
	int i;

	size = wcslen(s) + 1;
	for (i = 0; i <= 1; i++) {
		for (bufsize = 0; bufsize <= size + 10; bufsize++) {
			s1 = makebuf(bufsize * sizeof(wchar_t), i);
			wmemcpy(s1, s, bufsize <= size ? bufsize : size);
			len = (size > bufsize) ? bufsize : size - 1;
			ATF_CHECK(wcsnlen(s1, bufsize) == len);
		}
	}
}