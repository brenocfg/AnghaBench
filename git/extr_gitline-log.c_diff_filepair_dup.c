#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct diff_filepair {TYPE_2__* two; TYPE_1__* one; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 struct diff_filepair* xmalloc (int) ; 

__attribute__((used)) static struct diff_filepair *diff_filepair_dup(struct diff_filepair *pair)
{
	struct diff_filepair *new_filepair = xmalloc(sizeof(struct diff_filepair));
	new_filepair->one = pair->one;
	new_filepair->two = pair->two;
	new_filepair->one->count++;
	new_filepair->two->count++;
	return new_filepair;
}