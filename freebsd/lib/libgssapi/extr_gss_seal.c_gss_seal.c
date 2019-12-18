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
typedef  int /*<<< orphan*/  gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  gss_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

OM_uint32
gss_seal(OM_uint32 *minor_status,
    gss_ctx_id_t context_handle,
    int conf_req_flag,
    int qop_req,
    gss_buffer_t input_message_buffer,
    int *conf_state,
    gss_buffer_t output_message_buffer)
{

	return (gss_wrap(minor_status,
		    context_handle, conf_req_flag, qop_req,
		    input_message_buffer, conf_state,
		    output_message_buffer));
}