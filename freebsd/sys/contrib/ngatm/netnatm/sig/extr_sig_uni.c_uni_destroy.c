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
struct uni {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INS_FREE (struct uni*) ; 
 int /*<<< orphan*/  TIMER_DESTROY_UNI (struct uni*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t309 ; 
 int /*<<< orphan*/  t316 ; 
 int /*<<< orphan*/  t317 ; 
 int /*<<< orphan*/  uni_stop (struct uni*) ; 

void 
uni_destroy(struct uni *uni)
{
	uni_stop(uni);

	TIMER_DESTROY_UNI(uni, t309);
	TIMER_DESTROY_UNI(uni, t316);
	TIMER_DESTROY_UNI(uni, t317);

	INS_FREE(uni);
}