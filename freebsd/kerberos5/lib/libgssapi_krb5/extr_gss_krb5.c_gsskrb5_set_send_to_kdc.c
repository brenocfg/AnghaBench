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
struct gsskrb5_send_to_kdc {int dummy; } ;
struct TYPE_3__ {int length; struct gsskrb5_send_to_kdc* value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_KRB5_SEND_TO_KDC_X ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  gss_set_sec_context_option (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

OM_uint32
gsskrb5_set_send_to_kdc(struct gsskrb5_send_to_kdc *c)
{
    gss_buffer_desc buffer;
    OM_uint32 junk;

    if (c) {
	buffer.value = c;
	buffer.length = sizeof(*c);
    } else {
	buffer.value = NULL;
	buffer.length = 0;
    }

    gss_set_sec_context_option(&junk, NULL,
	    GSS_KRB5_SEND_TO_KDC_X, &buffer);

    return (GSS_S_COMPLETE);
}