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
struct eapol_test_data {scalar_t__ eapol_test_num_reauths; scalar_t__ ctrl_iface; scalar_t__ id_req_sent; } ;
struct eapol_sm {int dummy; } ;
typedef  enum eapol_supp_result { ____Placeholder_eapol_supp_result } eapol_supp_result ;

/* Variables and functions */
 int /*<<< orphan*/  eapol_sm_reauth ; 
 int /*<<< orphan*/  eapol_test_compare_pmk (struct eapol_test_data*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct eapol_test_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_terminate () ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void eapol_sm_cb(struct eapol_sm *eapol, enum eapol_supp_result result,
			void *ctx)
{
	struct eapol_test_data *e = ctx;
	printf("eapol_sm_cb: result=%d\n", result);
	e->id_req_sent = 0;
	if (e->ctrl_iface)
		return;
	e->eapol_test_num_reauths--;
	if (e->eapol_test_num_reauths < 0)
		eloop_terminate();
	else {
		eapol_test_compare_pmk(e);
		eloop_register_timeout(0, 100000, eapol_sm_reauth, e, NULL);
	}
}