#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  balance; struct TYPE_3__* rlink; struct TYPE_3__* llink; } ;
typedef  TYPE_1__ posix_tnode ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK (int) ; 
 int /*<<< orphan*/  ATF_CHECK_EQ (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int
tnode_assert(const posix_tnode *n)
{
	unsigned int height_left, height_right;
	int balance;

	if (n == NULL)
		return 0;
	height_left = tnode_assert(n->llink);
	height_right = tnode_assert(n->rlink);
	balance = (int)height_left - (int)height_right;
	ATF_CHECK(balance >= -1);
	ATF_CHECK(balance <= 1);
	ATF_CHECK_EQ(balance, n->balance);
	return (height_left > height_right ? height_left : height_right) + 1;
}