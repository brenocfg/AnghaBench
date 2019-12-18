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
struct alq {int /*<<< orphan*/  aq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_ACTIVE ; 
 int /*<<< orphan*/  LIST_REMOVE (struct alq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_act ; 

__attribute__((used)) static void
ald_deactivate(struct alq *alq)
{
	LIST_REMOVE(alq, aq_act);
	alq->aq_flags &= ~AQ_ACTIVE;
}