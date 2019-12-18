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
struct call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGC_T301 ; 
 int /*<<< orphan*/  uni_enq_call (struct call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
t301_func(struct call *c)
{
	uni_enq_call(c, SIGC_T301, 0, NULL, NULL);
}