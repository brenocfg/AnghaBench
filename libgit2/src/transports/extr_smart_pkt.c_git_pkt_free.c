#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* symref_target; TYPE_5__* name; } ;
struct TYPE_9__ {TYPE_1__ head; } ;
typedef  TYPE_2__ git_pkt_ref ;
struct TYPE_10__ {TYPE_5__* ref; } ;
typedef  TYPE_3__ git_pkt_ok ;
struct TYPE_11__ {TYPE_5__* msg; TYPE_5__* ref; } ;
typedef  TYPE_4__ git_pkt_ng ;
struct TYPE_12__ {scalar_t__ type; } ;
typedef  TYPE_5__ git_pkt ;

/* Variables and functions */
 scalar_t__ GIT_PKT_NG ; 
 scalar_t__ GIT_PKT_OK ; 
 scalar_t__ GIT_PKT_REF ; 
 int /*<<< orphan*/  git__free (TYPE_5__*) ; 

void git_pkt_free(git_pkt *pkt)
{
	if (pkt == NULL) {
		return;
	}
	if (pkt->type == GIT_PKT_REF) {
		git_pkt_ref *p = (git_pkt_ref *) pkt;
		git__free(p->head.name);
		git__free(p->head.symref_target);
	}

	if (pkt->type == GIT_PKT_OK) {
		git_pkt_ok *p = (git_pkt_ok *) pkt;
		git__free(p->ref);
	}

	if (pkt->type == GIT_PKT_NG) {
		git_pkt_ng *p = (git_pkt_ng *) pkt;
		git__free(p->ref);
		git__free(p->msg);
	}

	git__free(pkt);
}