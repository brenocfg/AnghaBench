#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* set_callbacks ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ git_transport ;
struct TYPE_7__ {int /*<<< orphan*/  payload; int /*<<< orphan*/  certificate_check; int /*<<< orphan*/  sideband_progress; } ;
typedef  TYPE_2__ git_remote_callbacks ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int set_transport_callbacks(git_transport *t, const git_remote_callbacks *cbs)
{
	if (!t->set_callbacks || !cbs)
		return 0;

	return t->set_callbacks(t, cbs->sideband_progress, NULL,
				cbs->certificate_check, cbs->payload);
}