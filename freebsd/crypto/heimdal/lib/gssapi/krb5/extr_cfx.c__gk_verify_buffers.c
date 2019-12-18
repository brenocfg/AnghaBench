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
typedef  int /*<<< orphan*/  gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_iov_buffer_desc ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 scalar_t__ IS_DCE_STYLE (int /*<<< orphan*/  const) ; 

OM_uint32
_gk_verify_buffers(OM_uint32 *minor_status,
		   const gsskrb5_ctx ctx,
		   const gss_iov_buffer_desc *header,
		   const gss_iov_buffer_desc *padding,
		   const gss_iov_buffer_desc *trailer)
{
    if (header == NULL) {
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }

    if (IS_DCE_STYLE(ctx)) {
	/*
	 * In DCE style mode we reject having a padding or trailer buffer
	 */
	if (padding) {
	    *minor_status = EINVAL;
	    return GSS_S_FAILURE;
	}
	if (trailer) {
	    *minor_status = EINVAL;
	    return GSS_S_FAILURE;
	}
    } else {
	/*
	 * In non-DCE style mode we require having a padding buffer
	 */
	if (padding == NULL) {
	    *minor_status = EINVAL;
	    return GSS_S_FAILURE;
	}
    }

    *minor_status = 0;
    return GSS_S_COMPLETE;
}