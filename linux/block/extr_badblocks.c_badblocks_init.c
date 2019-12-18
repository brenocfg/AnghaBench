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
struct badblocks {int dummy; } ;

/* Variables and functions */
 int __badblocks_init (int /*<<< orphan*/ *,struct badblocks*,int) ; 

int badblocks_init(struct badblocks *bb, int enable)
{
	return __badblocks_init(NULL, bb, enable);
}