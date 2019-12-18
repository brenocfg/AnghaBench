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
typedef  int /*<<< orphan*/  uint32_t ;
struct call {size_t cstate; int /*<<< orphan*/  uni; } ;
struct TYPE_2__ {int /*<<< orphan*/  ext; } ;

/* Variables and functions */
 TYPE_1__* callstates ; 
 int /*<<< orphan*/  uniapi_uni_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
uniapi_call_error(struct call *c, uint32_t reason, uint32_t cookie)
{
	uniapi_uni_error(c->uni, reason, cookie, callstates[c->cstate].ext);
}