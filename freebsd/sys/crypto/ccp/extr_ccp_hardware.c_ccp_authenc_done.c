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
struct cryptop {struct cryptodesc* crp_desc; } ;
struct cryptodesc {struct cryptodesc* crd_next; } ;
struct ccp_session {scalar_t__ cipher_first; int /*<<< orphan*/  blkcipher; } ;
struct ccp_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccp_do_hmac_done (struct ccp_queue*,struct ccp_session*,struct cryptop*,struct cryptodesc*,int) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ccp_authenc_done(struct ccp_queue *qp, struct ccp_session *s, void *vcrp,
    int error)
{
	struct cryptodesc *crda;
	struct cryptop *crp;

	explicit_bzero(&s->blkcipher, sizeof(s->blkcipher));

	crp = vcrp;
	if (s->cipher_first)
		crda = crp->crp_desc->crd_next;
	else
		crda = crp->crp_desc;

	ccp_do_hmac_done(qp, s, crp, crda, error);
}