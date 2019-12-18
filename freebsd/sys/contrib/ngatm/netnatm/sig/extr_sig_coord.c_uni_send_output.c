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
struct uni_msg {int dummy; } ;
struct uni_all {int dummy; } ;
struct uni {scalar_t__ custat; int /*<<< orphan*/  arg; TYPE_1__* funcs; int /*<<< orphan*/  cx; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* saal_output ) (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*) ;} ;

/* Variables and functions */
 scalar_t__ CU_STAT0 ; 
 scalar_t__ CU_STAT1 ; 
 scalar_t__ CU_STAT2 ; 
 int /*<<< orphan*/  SAAL_DATA_request ; 
 int /*<<< orphan*/  SIGO_DATA ; 
 int /*<<< orphan*/  UNI_FAC_ERR ; 
 int /*<<< orphan*/  VERBOSE0 (struct uni*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*) ; 
 int /*<<< orphan*/  uni_delenq_coord (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*) ; 
 int uni_encode (struct uni_msg*,struct uni_all*,int /*<<< orphan*/ *) ; 
 struct uni_msg* uni_msg_alloc (int) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 

int
uni_send_output(struct uni_all *u, struct uni *uni)
{
	struct uni_msg *m;
	int err;

	if (uni->custat == CU_STAT0 || uni->custat == CU_STAT2)
		return (0);

	m = uni_msg_alloc(1024);
	if ((err = uni_encode(m, u, &uni->cx)) != 0) {
		VERBOSE0(uni, UNI_FAC_ERR, "uni_encode failed: %08x", err);
		uni_msg_destroy(m);
		return (-1);
	}
	if (uni->custat == CU_STAT1)
		uni_delenq_coord(uni, SIGO_DATA, 0, m);
	else
		uni->funcs->saal_output(uni, uni->arg, SAAL_DATA_request, m);
	return (0);
}