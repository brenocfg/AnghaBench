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
struct TYPE_3__ {int /*<<< orphan*/  suspect; } ;
typedef  TYPE_1__ git_blame__entry ;

/* Variables and functions */
 int /*<<< orphan*/  origin_decref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decref_split(git_blame__entry *split)
{
	int i;
	for (i=0; i<3; i++)
		origin_decref(split[i].suspect);
}