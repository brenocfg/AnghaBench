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
typedef  union authctx {int dummy; } authctx ;
struct TYPE_2__ {int /*<<< orphan*/  pads; struct auth_hash* auth_hash; } ;
struct ccr_session {TYPE_1__ hmac; } ;
struct auth_hash {int /*<<< orphan*/  (* Init ) (union authctx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (union authctx*) ; 
 int /*<<< orphan*/  t4_copy_partial_hash (int,union authctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ccr_init_hash_digest(struct ccr_session *s, int cri_alg)
{
	union authctx auth_ctx;
	struct auth_hash *axf;

	axf = s->hmac.auth_hash;
	axf->Init(&auth_ctx);
	t4_copy_partial_hash(cri_alg, &auth_ctx, s->hmac.pads);
}