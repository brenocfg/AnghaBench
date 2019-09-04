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
typedef  int /*<<< orphan*/  uint64_t ;
struct progress {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  display (struct progress*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void display_progress(struct progress *progress, uint64_t n)
{
	if (progress)
		display(progress, n, NULL);
}