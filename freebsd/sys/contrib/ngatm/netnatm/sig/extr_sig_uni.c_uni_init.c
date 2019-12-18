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
struct uni {int cref_alloc; void* glob_respond; void* glob_start; int /*<<< orphan*/  custat; scalar_t__ working; } ;

/* Variables and functions */
 int /*<<< orphan*/  CU_STAT0 ; 
 void* UNI_CALLSTATE_REST0 ; 

__attribute__((used)) static void
uni_init(struct uni *uni)
{
	uni->working = 0;
	uni->cref_alloc = 12;
	uni->custat = CU_STAT0;
	uni->glob_start = UNI_CALLSTATE_REST0;
	uni->glob_respond = UNI_CALLSTATE_REST0;
}