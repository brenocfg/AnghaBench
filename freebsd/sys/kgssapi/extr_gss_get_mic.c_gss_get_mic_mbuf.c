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
 scalar_t__ KGSS_GET_MIC (int /*<<< orphan*/  const,scalar_t__*,int /*<<< orphan*/ ,struct mbuf*,struct mbuf**) ; 

OM_uint32
gss_get_mic_mbuf(OM_uint32 *minor_status, const gss_ctx_id_t ctx,
    gss_qop_t qop_req, struct mbuf *m, struct mbuf **micp)
{

	if (!ctx) {
		*minor_status = 0;
		return (GSS_S_NO_CONTEXT);
	}

	return (KGSS_GET_MIC(ctx, minor_status, qop_req, m, micp));
}