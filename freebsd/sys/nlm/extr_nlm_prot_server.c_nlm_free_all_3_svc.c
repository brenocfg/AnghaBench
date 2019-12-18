#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct nlm4_notify {int /*<<< orphan*/  state; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ nlm_notify ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  nlm4_free_all_4_svc (struct nlm4_notify*,void*,struct svc_req*) ; 

bool_t
nlm_free_all_3_svc(nlm_notify *argp, void *result, struct svc_req *rqstp)
{
	struct nlm4_notify args4;

	args4.name = argp->name;
	args4.state = argp->state;

	return (nlm4_free_all_4_svc(&args4, result, rqstp));
}