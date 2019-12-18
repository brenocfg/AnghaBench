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
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  gsskrb5_ctx ;
typedef  size_t OM_uint32 ;

/* Variables and functions */
 size_t GSS_ARCFOUR_WRAP_TOKEN_SIZE ; 
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 size_t GSS_S_COMPLETE ; 
 scalar_t__ IS_DCE_STYLE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  _gssapi_encap_length (size_t,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gsskrb5_encap_length (size_t,size_t*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OM_uint32
max_wrap_length_arcfour(const gsskrb5_ctx ctx,
			krb5_crypto crypto,
			size_t input_length,
			OM_uint32 *max_input_size)
{
    /*
     * if GSS_C_DCE_STYLE is in use:
     *  - we only need to encapsulate the WRAP token
     * However, since this is a fixed since, we just
     */
    if (IS_DCE_STYLE(ctx)) {
	size_t len, total_len;

	len = GSS_ARCFOUR_WRAP_TOKEN_SIZE;
	_gssapi_encap_length(len, &len, &total_len, GSS_KRB5_MECHANISM);

	if (input_length < len)
	    *max_input_size = 0;
	else
	    *max_input_size = input_length - len;

    } else {
	size_t extrasize = GSS_ARCFOUR_WRAP_TOKEN_SIZE;
	size_t blocksize = 8;
	size_t len, total_len;

	len = 8 + input_length + blocksize + extrasize;

	_gsskrb5_encap_length(len, &len, &total_len, GSS_KRB5_MECHANISM);

	total_len -= input_length; /* token length */
	if (total_len < input_length) {
	    *max_input_size = (input_length - total_len);
	    (*max_input_size) &= (~(OM_uint32)(blocksize - 1));
	} else {
	    *max_input_size = 0;
	}
    }

    return GSS_S_COMPLETE;
}