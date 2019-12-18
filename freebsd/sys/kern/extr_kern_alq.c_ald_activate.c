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
struct alq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct alq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ald_active ; 
 int /*<<< orphan*/  aq_act ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ald_activate(struct alq *alq)
{
	LIST_INSERT_HEAD(&ald_active, alq, aq_act);
	wakeup(&ald_active);
}