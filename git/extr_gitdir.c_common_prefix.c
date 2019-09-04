#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pathspec {TYPE_1__* items; } ;
struct TYPE_2__ {int /*<<< orphan*/  match; } ;

/* Variables and functions */
 unsigned long common_prefix_len (struct pathspec const*) ; 
 char* xmemdupz (int /*<<< orphan*/ ,unsigned long) ; 

char *common_prefix(const struct pathspec *pathspec)
{
	unsigned long len = common_prefix_len(pathspec);

	return len ? xmemdupz(pathspec->items[0].match, len) : NULL;
}