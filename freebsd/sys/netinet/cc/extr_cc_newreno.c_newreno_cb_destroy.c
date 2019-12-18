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
struct cc_var {int /*<<< orphan*/  cc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NEWRENO ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
newreno_cb_destroy(struct cc_var *ccv)
{
	free(ccv->cc_data, M_NEWRENO);
}