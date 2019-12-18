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
 int /*<<< orphan*/  bexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  not_equal () ; 
 int /*<<< orphan*/  not_greater () ; 
 int /*<<< orphan*/  not_less () ; 
 int readch () ; 
 int /*<<< orphan*/  readline () ; 
 int /*<<< orphan*/  unreadch () ; 

__attribute__((used)) static void
not_compare(void)
{

	switch (readch()) {
	case '<':
		not_less();
		break;
	case '>':
		not_greater();
		break;
	case '=':
		not_equal();
		break;
	default:
		unreadch();
		bexec(readline());
		break;
	}
}