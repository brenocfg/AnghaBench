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
struct ipsec_ctx_data {int af; int /*<<< orphan*/ ** mp; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EACCES ; 
 int EPFNOSUPPORT ; 
 int /*<<< orphan*/  HHOOKS_RUN_IF (int /*<<< orphan*/ ,struct ipsec_ctx_data*,int /*<<< orphan*/ *) ; 
 int HHOOK_IPSEC_INET ; 
 int HHOOK_IPSEC_INET6 ; 
 int HHOOK_TYPE_IPSEC_IN ; 
 int /*<<< orphan*/ * V_ipsec_hhh_in ; 
 int /*<<< orphan*/ * V_ipsec_hhh_out ; 

int
ipsec_run_hhooks(struct ipsec_ctx_data *ctx, int type)
{
	int idx;

	switch (ctx->af) {
#ifdef INET
	case AF_INET:
		idx = HHOOK_IPSEC_INET;
		break;
#endif
#ifdef INET6
	case AF_INET6:
		idx = HHOOK_IPSEC_INET6;
		break;
#endif
	default:
		return (EPFNOSUPPORT);
	}
	if (type == HHOOK_TYPE_IPSEC_IN)
		HHOOKS_RUN_IF(V_ipsec_hhh_in[idx], ctx, NULL);
	else
		HHOOKS_RUN_IF(V_ipsec_hhh_out[idx], ctx, NULL);
	if (*ctx->mp == NULL)
		return (EACCES);
	return (0);
}