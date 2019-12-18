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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ OR ; 
 int /*<<< orphan*/  concat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * op2 (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  primary () ; 
 scalar_t__ relex () ; 
 scalar_t__ rtok ; 

Node *alt(Node *np)
{
	if (rtok == OR) {
		rtok = relex();
		return (alt(op2(OR, np, concat(primary()))));
	}
	return (np);
}