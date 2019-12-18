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
struct cfiscsi_target {int /*<<< orphan*/  ct_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfiscsi_target_hold(struct cfiscsi_target *ct)
{

	refcount_acquire(&ct->ct_refcount);
}