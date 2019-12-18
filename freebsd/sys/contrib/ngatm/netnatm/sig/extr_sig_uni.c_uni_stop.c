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
struct uni {int /*<<< orphan*/  delq; int /*<<< orphan*/  workq; int /*<<< orphan*/  calls; } ;
struct call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGQ_CLEAR (int /*<<< orphan*/ *) ; 
 struct call* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  uni_destroy_call (struct call*,int) ; 

__attribute__((used)) static void
uni_stop(struct uni *uni)
{
	struct call *c;

	while ((c = TAILQ_FIRST(&uni->calls)) != NULL) {
		TAILQ_REMOVE(&uni->calls, c, link);
		uni_destroy_call(c, 1);
	}

	SIGQ_CLEAR(&uni->workq);
	SIGQ_CLEAR(&uni->delq);
}