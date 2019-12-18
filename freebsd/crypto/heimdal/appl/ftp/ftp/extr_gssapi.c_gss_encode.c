#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gssapi_data {int /*<<< orphan*/  context_hdl; } ;
struct TYPE_4__ {int length; void* value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 int /*<<< orphan*/  gss_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int*,TYPE_1__*) ; 
 int prot_private ; 

__attribute__((used)) static int
gss_encode(void *app_data, void *from, int length, int level, void **to)
{
    OM_uint32 maj_stat, min_stat;
    gss_buffer_desc input, output;
    int conf_state;
    struct gssapi_data *d = app_data;

    input.length = length;
    input.value = from;
    maj_stat = gss_wrap (&min_stat,
			 d->context_hdl,
			 level == prot_private,
			 GSS_C_QOP_DEFAULT,
			 &input,
			 &conf_state,
			 &output);
    *to = output.value;
    return output.length;
}