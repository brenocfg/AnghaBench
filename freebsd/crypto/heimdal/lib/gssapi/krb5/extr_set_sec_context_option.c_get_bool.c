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
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_3__ {int length; int /*<<< orphan*/ * value; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 

__attribute__((used)) static OM_uint32
get_bool(OM_uint32 *minor_status,
	 const gss_buffer_t value,
	 int *flag)
{
    if (value->value == NULL || value->length != 1) {
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }
    *flag = *((const char *)value->value) != 0;
    return GSS_S_COMPLETE;
}