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

/* Variables and functions */
 int /*<<< orphan*/  free ; 
 scalar_t__ thr_keycreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyname_key ; 
 int ttyname_keycreated ; 

__attribute__((used)) static void
ttyname_keycreate(void)
{
	ttyname_keycreated = (thr_keycreate(&ttyname_key, free) == 0);
}