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
struct mbuf {int dummy; } ;
struct krb5_context {scalar_t__ kc_lifetime; TYPE_2__* kc_tokenkey; } ;
typedef  scalar_t__ gss_qop_t ;
typedef  scalar_t__ gss_ctx_id_t ;
struct TYPE_4__ {TYPE_1__* ks_class; } ;
struct TYPE_3__ {int ec_type; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
#define  ETYPE_ARCFOUR_HMAC_MD5 131 
#define  ETYPE_ARCFOUR_HMAC_MD5_56 130 
#define  ETYPE_DES3_CBC_SHA1 129 
#define  ETYPE_DES_CBC_CRC 128 
 scalar_t__ GSS_C_QOP_DEFAULT ; 
 scalar_t__ GSS_S_BAD_QOP ; 
 scalar_t__ GSS_S_CONTEXT_EXPIRED ; 
 scalar_t__ GSS_S_FAILURE ; 
 scalar_t__ krb5_get_mic_new (struct krb5_context*,struct mbuf*,struct mbuf**) ; 
 scalar_t__ krb5_get_mic_old (struct krb5_context*,struct mbuf*,struct mbuf**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgn_alg_des3_sha1 ; 
 int /*<<< orphan*/  sgn_alg_des_md5 ; 
 int /*<<< orphan*/  sgn_alg_hmac_md5 ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static OM_uint32
krb5_get_mic(gss_ctx_id_t ctx, OM_uint32 *minor_status,
    gss_qop_t qop_req, struct mbuf *m, struct mbuf **micp)
{
	struct krb5_context *kc = (struct krb5_context *)ctx;

	*minor_status = 0;

	if (qop_req != GSS_C_QOP_DEFAULT)
		return (GSS_S_BAD_QOP);

	if (time_uptime > kc->kc_lifetime)
		return (GSS_S_CONTEXT_EXPIRED);

	switch (kc->kc_tokenkey->ks_class->ec_type) {
	case ETYPE_DES_CBC_CRC:
		return (krb5_get_mic_old(kc, m, micp, sgn_alg_des_md5));

	case ETYPE_DES3_CBC_SHA1:
		return (krb5_get_mic_old(kc, m, micp, sgn_alg_des3_sha1));

	case ETYPE_ARCFOUR_HMAC_MD5:
	case ETYPE_ARCFOUR_HMAC_MD5_56:
		return (krb5_get_mic_old(kc, m, micp, sgn_alg_hmac_md5));

	default:
		return (krb5_get_mic_new(kc, m, micp));
	}

	return (GSS_S_FAILURE);
}