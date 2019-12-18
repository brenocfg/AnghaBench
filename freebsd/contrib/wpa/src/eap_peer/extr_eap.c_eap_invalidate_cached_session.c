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
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_deinit_prev_method (struct eap_sm*,char*) ; 

void eap_invalidate_cached_session(struct eap_sm *sm)
{
	if (sm)
		eap_deinit_prev_method(sm, "invalidate");
}