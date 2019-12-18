#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_2__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_qop_t ;
struct TYPE_11__ {size_t length; } ;
struct TYPE_13__ {TYPE_1__ buffer; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ gss_iov_buffer_desc ;
typedef  int /*<<< orphan*/  gss_cfx_wrap_token_desc ;
struct TYPE_12__ {int /*<<< orphan*/  crypto; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  GSSAPI_KRB5_INIT (int /*<<< orphan*/ *) ; 
 int GSS_IOV_BUFFER_TYPE (int /*<<< orphan*/ ) ; 
#define  GSS_IOV_BUFFER_TYPE_DATA 133 
#define  GSS_IOV_BUFFER_TYPE_EMPTY 132 
#define  GSS_IOV_BUFFER_TYPE_HEADER 131 
#define  GSS_IOV_BUFFER_TYPE_PADDING 130 
#define  GSS_IOV_BUFFER_TYPE_SIGN_ONLY 129 
#define  GSS_IOV_BUFFER_TYPE_TRAILER 128 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 scalar_t__ IS_DCE_STYLE (TYPE_2__*) ; 
 int /*<<< orphan*/  KRB5_CRYPTO_TYPE_CHECKSUM ; 
 int /*<<< orphan*/  KRB5_CRYPTO_TYPE_HEADER ; 
 int /*<<< orphan*/  KRB5_CRYPTO_TYPE_PADDING ; 
 int /*<<< orphan*/  KRB5_CRYPTO_TYPE_TRAILER ; 
 scalar_t__ _gk_verify_buffers (scalar_t__*,TYPE_2__*,TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ krb5_crypto_getblocksize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ krb5_crypto_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

OM_uint32
_gssapi_wrap_iov_length_cfx(OM_uint32 *minor_status,
			    gsskrb5_ctx ctx,
			    krb5_context context,
			    int conf_req_flag,
			    gss_qop_t qop_req,
			    int *conf_state,
			    gss_iov_buffer_desc *iov,
			    int iov_count)
{
    OM_uint32 major_status;
    size_t size;
    int i;
    gss_iov_buffer_desc *header = NULL;
    gss_iov_buffer_desc *padding = NULL;
    gss_iov_buffer_desc *trailer = NULL;
    size_t gsshsize = 0;
    size_t gsstsize = 0;
    size_t k5hsize = 0;
    size_t k5tsize = 0;

    GSSAPI_KRB5_INIT (&context);
    *minor_status = 0;

    for (size = 0, i = 0; i < iov_count; i++) {
	switch(GSS_IOV_BUFFER_TYPE(iov[i].type)) {
	case GSS_IOV_BUFFER_TYPE_EMPTY:
	    break;
	case GSS_IOV_BUFFER_TYPE_DATA:
	    size += iov[i].buffer.length;
	    break;
	case GSS_IOV_BUFFER_TYPE_HEADER:
	    if (header != NULL) {
		*minor_status = 0;
		return GSS_S_FAILURE;
	    }
	    header = &iov[i];
	    break;
	case GSS_IOV_BUFFER_TYPE_TRAILER:
	    if (trailer != NULL) {
		*minor_status = 0;
		return GSS_S_FAILURE;
	    }
	    trailer = &iov[i];
	    break;
	case GSS_IOV_BUFFER_TYPE_PADDING:
	    if (padding != NULL) {
		*minor_status = 0;
		return GSS_S_FAILURE;
	    }
	    padding = &iov[i];
	    break;
	case GSS_IOV_BUFFER_TYPE_SIGN_ONLY:
	    break;
	default:
	    *minor_status = EINVAL;
	    return GSS_S_FAILURE;
	}
    }

    major_status = _gk_verify_buffers(minor_status, ctx, header, padding, trailer);
    if (major_status != GSS_S_COMPLETE) {
	    return major_status;
    }

    if (conf_req_flag) {
	size_t k5psize = 0;
	size_t k5pbase = 0;
	size_t k5bsize = 0;
	size_t ec = 0;

	size += sizeof(gss_cfx_wrap_token_desc);

	*minor_status = krb5_crypto_length(context, ctx->crypto,
					   KRB5_CRYPTO_TYPE_HEADER,
					   &k5hsize);
	if (*minor_status)
	    return GSS_S_FAILURE;

	*minor_status = krb5_crypto_length(context, ctx->crypto,
					   KRB5_CRYPTO_TYPE_TRAILER,
					   &k5tsize);
	if (*minor_status)
	    return GSS_S_FAILURE;

	*minor_status = krb5_crypto_length(context, ctx->crypto,
					   KRB5_CRYPTO_TYPE_PADDING,
					   &k5pbase);
	if (*minor_status)
	    return GSS_S_FAILURE;

	if (k5pbase > 1) {
	    k5psize = k5pbase - (size % k5pbase);
	} else {
	    k5psize = 0;
	}

	if (k5psize == 0 && IS_DCE_STYLE(ctx)) {
	    *minor_status = krb5_crypto_getblocksize(context, ctx->crypto,
						     &k5bsize);
	    if (*minor_status)
		return GSS_S_FAILURE;

	    ec = k5bsize;
	} else {
	    ec = k5psize;
	}

	gsshsize = sizeof(gss_cfx_wrap_token_desc) + k5hsize;
	gsstsize = sizeof(gss_cfx_wrap_token_desc) + ec + k5tsize;
    } else {
	*minor_status = krb5_crypto_length(context, ctx->crypto,
					   KRB5_CRYPTO_TYPE_CHECKSUM,
					   &k5tsize);
	if (*minor_status)
	    return GSS_S_FAILURE;

	gsshsize = sizeof(gss_cfx_wrap_token_desc);
	gsstsize = k5tsize;
    }

    if (trailer != NULL) {
	trailer->buffer.length = gsstsize;
    } else {
	gsshsize += gsstsize;
    }

    header->buffer.length = gsshsize;

    if (padding) {
	/* padding is done via EC and is contained in the header or trailer */
	padding->buffer.length = 0;
    }

    if (conf_state) {
	*conf_state = conf_req_flag;
    }

    return GSS_S_COMPLETE;
}