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
typedef  int /*<<< orphan*/  thrd_t ;

/* Variables and functions */
 int pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
thrd_equal(thrd_t thr0, thrd_t thr1)
{

	return (pthread_equal(thr0, thr1));
}