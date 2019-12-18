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
typedef  size_t uint16_t ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_cksumtype ;
typedef  int /*<<< orphan*/  gss_cfx_wrap_token_desc ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ krb5_checksumsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ krb5_crypto_get_checksum_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_crypto_getblocksize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ krb5_crypto_getpadsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ krb5_get_wrapped_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

krb5_error_code
_gsskrb5cfx_wrap_length_cfx(krb5_context context,
			    krb5_crypto crypto,
			    int conf_req_flag,
			    int dce_style,
			    size_t input_length,
			    size_t *output_length,
			    size_t *cksumsize,
			    uint16_t *padlength)
{
    krb5_error_code ret;
    krb5_cksumtype type;

    /* 16-byte header is always first */
    *output_length = sizeof(gss_cfx_wrap_token_desc);
    *padlength = 0;

    ret = krb5_crypto_get_checksum_type(context, crypto, &type);
    if (ret)
	return ret;

    ret = krb5_checksumsize(context, type, cksumsize);
    if (ret)
	return ret;

    if (conf_req_flag) {
	size_t padsize;

	/* Header is concatenated with data before encryption */
	input_length += sizeof(gss_cfx_wrap_token_desc);

	if (dce_style) {
		ret = krb5_crypto_getblocksize(context, crypto, &padsize);
	} else {
		ret = krb5_crypto_getpadsize(context, crypto, &padsize);
	}
	if (ret) {
	    return ret;
	}
	if (padsize > 1) {
	    /* XXX check this */
	    *padlength = padsize - (input_length % padsize);

	    /* We add the pad ourselves (noted here for completeness only) */
	    input_length += *padlength;
	}

	*output_length += krb5_get_wrapped_length(context,
						  crypto, input_length);
    } else {
	/* Checksum is concatenated with data */
	*output_length += input_length + *cksumsize;
    }

    assert(*output_length > input_length);

    return 0;
}