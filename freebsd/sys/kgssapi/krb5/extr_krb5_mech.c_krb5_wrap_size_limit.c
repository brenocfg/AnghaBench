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
struct krb5_encryption_class {int ec_type; int /*<<< orphan*/  ec_checksumlen; int /*<<< orphan*/  ec_msgblocklen; int /*<<< orphan*/  ec_blocklen; } ;
struct krb5_context {TYPE_1__* kc_tokenkey; } ;
typedef  scalar_t__ gss_qop_t ;
typedef  scalar_t__ gss_ctx_id_t ;
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
struct TYPE_3__ {struct krb5_encryption_class* ks_class; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
#define  ETYPE_ARCFOUR_HMAC_MD5 131 
#define  ETYPE_ARCFOUR_HMAC_MD5_56 130 
#define  ETYPE_DES3_CBC_SHA1 129 
#define  ETYPE_DES_CBC_CRC 128 
 scalar_t__ GSS_C_QOP_DEFAULT ; 
 scalar_t__ GSS_S_BAD_QOP ; 
 scalar_t__ GSS_S_COMPLETE ; 
 TYPE_2__ krb5_mech_oid ; 

__attribute__((used)) static OM_uint32
krb5_wrap_size_limit(gss_ctx_id_t ctx, OM_uint32 *minor_status,
    int conf_req_flag, gss_qop_t qop_req, OM_uint32 req_output_size,
    OM_uint32 *max_input_size)
{
	struct krb5_context *kc = (struct krb5_context *)ctx;
	const struct krb5_encryption_class *ec;
	OM_uint32 overhead;

	*minor_status = 0;
	*max_input_size = 0;

	if (qop_req != GSS_C_QOP_DEFAULT)
		return (GSS_S_BAD_QOP);

	ec = kc->kc_tokenkey->ks_class;
	switch (ec->ec_type) {
	case ETYPE_DES_CBC_CRC:
	case ETYPE_DES3_CBC_SHA1:
	case ETYPE_ARCFOUR_HMAC_MD5: 
	case ETYPE_ARCFOUR_HMAC_MD5_56:
		/*
		 * up to 5 bytes for [APPLICATION 0] SEQUENCE
		 * 2 + krb5 oid length
		 * 8 bytes of header
		 * 8 bytes of confounder
		 * maximum of 8 bytes of padding
		 * checksum
		 */
		overhead = 5 + 2 + krb5_mech_oid.length;
		overhead += 8 + 8 + ec->ec_msgblocklen;
		overhead += ec->ec_checksumlen;
		break;

	default:
		if (conf_req_flag) {
			/*
			 * 16 byts of header
			 * blocklen bytes of confounder
			 * up to msgblocklen - 1 bytes of padding
			 * 16 bytes for copy of header
			 * checksum
			 */
			overhead = 16 + ec->ec_blocklen;
			overhead += ec->ec_msgblocklen - 1;
			overhead += 16;
			overhead += ec->ec_checksumlen;
		} else {
			/*
			 * 16 bytes of header plus checksum.
			 */
			overhead = 16 + ec->ec_checksumlen;
		}
	}

	*max_input_size = req_output_size - overhead;

	return (GSS_S_COMPLETE);
}