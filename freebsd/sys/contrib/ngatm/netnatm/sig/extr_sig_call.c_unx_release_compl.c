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
struct uni_msg {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  act; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
struct uni_all {TYPE_2__ u; } ;
struct call {TYPE_3__* uni; } ;
struct TYPE_6__ {int /*<<< orphan*/  cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 int /*<<< orphan*/  uni_decode_body (struct uni_msg*,struct uni_all*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 int /*<<< orphan*/  uni_release_compl (struct call*,struct uni_all*) ; 
 int /*<<< orphan*/  uni_verify (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unx_release_compl(struct call *c, struct uni_msg *m, struct uni_all *u)
{

	(void)uni_decode_body(m, u, &c->uni->cx);
	(void)uni_verify(c->uni, u->u.hdr.act);	/* no point :-) */

	uni_release_compl(c, u);

	uni_msg_destroy(m);
	UNI_FREE(u);
}