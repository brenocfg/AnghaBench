#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct call {TYPE_1__* uni; scalar_t__ mine; int /*<<< orphan*/  cref; } ;
struct TYPE_2__ {int /*<<< orphan*/  cause; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CAUSE_TIMER (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MK_IE_CAUSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNI_CAUSE_LOC_USER ; 
 int /*<<< orphan*/  UNI_CAUSE_RECOVER ; 
 int /*<<< orphan*/  UNI_FAC_TIMEOUT ; 
 int /*<<< orphan*/  VERBOSE (TYPE_1__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_callD (struct call*) ; 

__attribute__((used)) static void
u8_t313(struct call *c)
{
	VERBOSE(c->uni, UNI_FAC_TIMEOUT, 1, "call %u/%s T313 tick",
	    c->cref, c->mine ? "mine" : "his");

	MK_IE_CAUSE(c->uni->cause, UNI_CAUSE_LOC_USER, UNI_CAUSE_RECOVER);
	ADD_CAUSE_TIMER(c->uni->cause, "313");
	clear_callD(c);
}