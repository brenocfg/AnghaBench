#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct kaiocb* p_aio; } ;
struct knote {int /*<<< orphan*/  kn_flags; int /*<<< orphan*/  kn_data; TYPE_1__ kn_ptr; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
struct TYPE_6__ {TYPE_2__ _aiocb_private; } ;
struct kaiocb {int jobflags; TYPE_3__ uaiocb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_EOF ; 
 int KAIOCB_FINISHED ; 

__attribute__((used)) static int
filt_aio(struct knote *kn, long hint)
{
	struct kaiocb *job = kn->kn_ptr.p_aio;

	kn->kn_data = job->uaiocb._aiocb_private.error;
	if (!(job->jobflags & KAIOCB_FINISHED))
		return (0);
	kn->kn_flags |= EV_EOF;
	return (1);
}