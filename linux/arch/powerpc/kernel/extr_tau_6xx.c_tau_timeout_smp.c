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
struct timer_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ shrink_timer ; 
 int /*<<< orphan*/  tau_timeout ; 
 int /*<<< orphan*/  tau_timer ; 

__attribute__((used)) static void tau_timeout_smp(struct timer_list *unused)
{

	/* schedule ourselves to be run again */
	mod_timer(&tau_timer, jiffies + shrink_timer) ;
	on_each_cpu(tau_timeout, NULL, 0);
}