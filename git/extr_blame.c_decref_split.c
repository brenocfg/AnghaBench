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
struct blame_entry {int /*<<< orphan*/  suspect; } ;

/* Variables and functions */
 int /*<<< orphan*/  blame_origin_decref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decref_split(struct blame_entry *split)
{
	int i;

	for (i = 0; i < 3; i++)
		blame_origin_decref(split[i].suspect);
}