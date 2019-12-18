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
struct itimer {int /*<<< orphan*/  it_mtx; int /*<<< orphan*/  it_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
realtimer_create(struct itimer *it)
{
	callout_init_mtx(&it->it_callout, &it->it_mtx, 0);
	return (0);
}