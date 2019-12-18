#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  alock; } ;
typedef  TYPE_2__ nlm4_unlockargs ;
struct TYPE_6__ {int /*<<< orphan*/  stat; } ;
struct TYPE_8__ {int /*<<< orphan*/  cookie; TYPE_1__ stat; } ;
typedef  TYPE_3__ nlm4_res ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_V4 ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  log_from_addr (char*,struct svc_req*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

nlm4_res *
nlm4_unlock_4_svc(nlm4_unlockargs *arg, struct svc_req *rqstp)
{
	static nlm4_res res;

	if (debug_level)
		log_from_addr("nlm4_unlock", rqstp);

	res.stat.stat = unlock(&arg->alock, LOCK_V4);
	res.cookie = arg->cookie;

	return (&res);
}