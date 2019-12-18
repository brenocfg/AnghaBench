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
typedef  int /*<<< orphan*/  tok_kind ;

/* Variables and functions */
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectbuf ; 
 int /*<<< orphan*/  s_print (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toktostr (int /*<<< orphan*/ ) ; 

void
expected3(tok_kind exp1, tok_kind exp2, tok_kind exp3)
{
	s_print(expectbuf, "expected '%s', '%s' or '%s'",
		toktostr(exp1),
		toktostr(exp2),
		toktostr(exp3));
	error(expectbuf);
}