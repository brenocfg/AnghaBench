#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  TYPE_2__* gssspnego_ctx ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
struct TYPE_9__ {int /*<<< orphan*/  value; int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ gss_buffer_desc ;
struct TYPE_8__ {int /*<<< orphan*/  negotiated_ctx_id; scalar_t__ verified_mic; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_DEFECTIVE_TOKEN ; 
 scalar_t__ GSS_S_DUPLICATE_TOKEN ; 
 scalar_t__ gss_verify_mic (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OM_uint32
verify_mechlist_mic
	   (OM_uint32 *minor_status,
	    gssspnego_ctx context_handle,
	    gss_buffer_t mech_buf,
	    heim_octet_string *mechListMIC
	   )
{
    OM_uint32 ret;
    gss_buffer_desc mic_buf;

    if (context_handle->verified_mic) {
	/* This doesn't make sense, we've already verified it? */
	*minor_status = 0;
	return GSS_S_DUPLICATE_TOKEN;
    }

    if (mechListMIC == NULL) {
	*minor_status = 0;
	return GSS_S_DEFECTIVE_TOKEN;
    }

    mic_buf.length = mechListMIC->length;
    mic_buf.value  = mechListMIC->data;

    ret = gss_verify_mic(minor_status,
			 context_handle->negotiated_ctx_id,
			 mech_buf,
			 &mic_buf,
			 NULL);

    if (ret != GSS_S_COMPLETE)
	ret = GSS_S_DEFECTIVE_TOKEN;

    return ret;
}