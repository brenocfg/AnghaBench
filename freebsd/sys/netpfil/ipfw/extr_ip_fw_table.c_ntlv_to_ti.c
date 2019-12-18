#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tid_info {int /*<<< orphan*/  tlen; TYPE_2__* tlvs; int /*<<< orphan*/  uidx; int /*<<< orphan*/  set; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
struct TYPE_5__ {TYPE_1__ head; int /*<<< orphan*/  idx; int /*<<< orphan*/  set; } ;
typedef  TYPE_2__ ipfw_obj_ntlv ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct tid_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ntlv_to_ti(ipfw_obj_ntlv *ntlv, struct tid_info *ti)
{

	memset(ti, 0, sizeof(struct tid_info));
	ti->set = ntlv->set;
	ti->uidx = ntlv->idx;
	ti->tlvs = ntlv;
	ti->tlen = ntlv->head.length;
}