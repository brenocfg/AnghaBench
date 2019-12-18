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
 scalar_t__ EOF ; 
 scalar_t__ EQUAL ; 
 scalar_t__ compare (int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ putchar (char) ; 

__attribute__((used)) static void
print_from(wchar_t *string, unsigned char *front, unsigned char *back)
{
	for (; front < back && compare(string, front, back) == EQUAL; ++front) {
		for (; front < back && *front != '\n'; ++front)
			if (putchar(*front) == EOF)
				err(2, "stdout");
		if (putchar('\n') == EOF)
			err(2, "stdout");
	}
}