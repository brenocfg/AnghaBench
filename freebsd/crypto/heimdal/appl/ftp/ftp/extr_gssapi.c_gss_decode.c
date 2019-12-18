#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gssapi_data {int /*<<< orphan*/  context_hdl; } ;
typedef  int /*<<< orphan*/  gss_qop_t ;
struct TYPE_5__ {int length; void* value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_unwrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (void*,void*,int) ; 

__attribute__((used)) static int
gss_decode(void *app_data, void *buf, int len, int level)
{
    OM_uint32 maj_stat, min_stat;
    gss_buffer_desc input, output;
    gss_qop_t qop_state;
    int conf_state;
    struct gssapi_data *d = app_data;
    size_t ret_len;

    input.length = len;
    input.value = buf;
    maj_stat = gss_unwrap (&min_stat,
			   d->context_hdl,
			   &input,
			   &output,
			   &conf_state,
			   &qop_state);
    if(GSS_ERROR(maj_stat))
	return -1;
    memmove(buf, output.value, output.length);
    ret_len = output.length;
    gss_release_buffer(&min_stat, &output);
    return ret_len;
}