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
struct count {scalar_t__ y; int x; } ;

/* Variables and functions */

__attribute__((used)) static int compare(struct count *a, struct count *b) {
	if (a->y == b->y)
		return a->x - b->x;
	return a->y - b->y;
}