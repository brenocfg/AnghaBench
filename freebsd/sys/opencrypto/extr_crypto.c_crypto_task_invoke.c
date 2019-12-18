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
struct cryptop {int /*<<< orphan*/  crp_session; } ;
struct cryptocap {int dummy; } ;

/* Variables and functions */
 int ERESTART ; 
 int /*<<< orphan*/  crypto_batch_enqueue (struct cryptop*) ; 
 struct cryptocap* crypto_checkdriver (int) ; 
 int crypto_invoke (struct cryptocap*,struct cryptop*,int /*<<< orphan*/ ) ; 
 int crypto_ses2hid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
crypto_task_invoke(void *ctx, int pending)
{
	struct cryptocap *cap;
	struct cryptop *crp;
	int hid, result;

	crp = (struct cryptop *)ctx;

	hid = crypto_ses2hid(crp->crp_session);
	cap = crypto_checkdriver(hid);

	result = crypto_invoke(cap, crp, 0);
	if (result == ERESTART)
		crypto_batch_enqueue(crp);
}