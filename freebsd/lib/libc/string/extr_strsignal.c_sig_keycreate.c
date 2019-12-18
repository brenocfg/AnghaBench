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
 int /*<<< orphan*/  sig_key ; 
 int sig_keycreated ; 
 scalar_t__ thr_keycreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sig_keycreate(void)
{
	sig_keycreated = (thr_keycreate(&sig_key, free) == 0);
}