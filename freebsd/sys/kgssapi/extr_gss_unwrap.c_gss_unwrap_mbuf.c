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
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  gss_qop_t ;
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_NO_CONTEXT ; 
 scalar_t__ KGSS_UNWRAP (int /*<<< orphan*/  const,scalar_t__*,struct mbuf**,int*,int /*<<< orphan*/ *) ; 

OM_uint32
gss_unwrap_mbuf(OM_uint32 *minor_status,
    const gss_ctx_id_t ctx,
    struct mbuf **mp,
    int *conf_state,
    gss_qop_t *qop_state)
{

	if (!ctx) {
		*minor_status = 0;
		return (GSS_S_NO_CONTEXT);
	}

	return (KGSS_UNWRAP(ctx, minor_status, mp, conf_state, qop_state));
}