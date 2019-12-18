#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tac_author_request {int authen_meth; int authen_type; int service; int /*<<< orphan*/  priv_lvl; } ;
struct TYPE_3__ {struct tac_author_request author_request; } ;
struct TYPE_4__ {TYPE_1__ u; } ;
struct tac_handle {TYPE_2__ request; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAC_AUTHOR ; 
 int /*<<< orphan*/  TAC_PRIV_LVL_USER ; 
 int /*<<< orphan*/  create_msg (struct tac_handle*,int /*<<< orphan*/ ,int,int) ; 

int
tac_create_author(struct tac_handle *h, int method, int type, int service)
{
	struct tac_author_request *areq;

	create_msg(h, TAC_AUTHOR, method, type);

	areq = &h->request.u.author_request;
	areq->authen_meth = method;
	areq->priv_lvl = TAC_PRIV_LVL_USER;
	areq->authen_type = type;
	areq->service = service;

	return 0;
}