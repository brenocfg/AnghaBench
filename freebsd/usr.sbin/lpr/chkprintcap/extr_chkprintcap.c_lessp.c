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
struct TYPE_2__ {scalar_t__ st_dev; scalar_t__ st_ino; } ;
struct dirlist {TYPE_1__ stab; } ;

/* Variables and functions */

__attribute__((used)) static int
lessp(const struct dirlist *a, const struct dirlist *b)
{
	if (a->stab.st_dev == b->stab.st_dev)
		return a->stab.st_ino < b->stab.st_ino;
	return a->stab.st_dev < b->stab.st_dev;
}