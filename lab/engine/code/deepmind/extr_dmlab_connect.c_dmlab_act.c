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
 int /*<<< orphan*/  dmlab_act_continuous (void*,double const*) ; 
 int /*<<< orphan*/  dmlab_act_discrete (void*,int const*) ; 

__attribute__((used)) static void dmlab_act(void* context, const int act_d[], const double act_c[]) {
  dmlab_act_discrete(context, act_d);
  dmlab_act_continuous(context, act_c);
}