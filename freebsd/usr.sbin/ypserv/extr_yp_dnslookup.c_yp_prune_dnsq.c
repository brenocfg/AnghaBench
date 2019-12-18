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
struct circleq_dnsentry {struct circleq_dnsentry* name; int /*<<< orphan*/  ttl; } ;

/* Variables and functions */
 struct circleq_dnsentry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct circleq_dnsentry* TAILQ_NEXT (struct circleq_dnsentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct circleq_dnsentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct circleq_dnsentry*) ; 
 int /*<<< orphan*/  links ; 
 scalar_t__ pending ; 
 int /*<<< orphan*/  qhead ; 

void
yp_prune_dnsq(void)
{
	register struct circleq_dnsentry *q, *n;

	q = TAILQ_FIRST(&qhead);
	while (q != NULL) {
		q->ttl--;
		n = TAILQ_NEXT(q, links);
		if (!q->ttl) {
			TAILQ_REMOVE(&qhead, q, links);
			free(q->name);
			free(q);
			pending--;
		}
		q = n;
	}

	if (pending < 0)
		pending = 0;

	return;
}