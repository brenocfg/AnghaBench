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
typedef  size_t off_t ;

/* Variables and functions */
 int /*<<< orphan*/  bandwidth_limit (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  bwlimit ; 
 scalar_t__ limit_kbps ; 

__attribute__((used)) static int
scpio(void *_cnt, size_t s)
{
	off_t *cnt = (off_t *)_cnt;

	*cnt += s;
	if (limit_kbps > 0)
		bandwidth_limit(&bwlimit, s);
	return 0;
}