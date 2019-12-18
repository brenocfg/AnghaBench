#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_KRB5_CCACHE_NAME_X ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  gss_set_sec_context_option (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rk_UNCONST (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

OM_uint32
gss_krb5_ccache_name(OM_uint32 *minor_status, 
		     const char *name,
		     const char **out_name)
{
    gss_buffer_desc buffer;
    OM_uint32 junk;

    if (out_name)
	*out_name = NULL;

    buffer.value = rk_UNCONST(name);
    buffer.length = strlen(name);

    gss_set_sec_context_option(&junk, NULL,
	    GSS_KRB5_CCACHE_NAME_X, &buffer);

    return (GSS_S_COMPLETE);
}