#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct party {TYPE_1__* call; } ;
struct TYPE_4__ {int /*<<< orphan*/  ext; } ;
struct TYPE_3__ {size_t cstate; int /*<<< orphan*/  uni; } ;

/* Variables and functions */
 TYPE_2__* callstates ; 
 int /*<<< orphan*/  uniapi_uni_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
uniapi_party_error(struct party *p, uint32_t reason, uint32_t cookie)
{
	uniapi_uni_error(p->call->uni, reason, cookie,
	    callstates[p->call->cstate].ext);
}