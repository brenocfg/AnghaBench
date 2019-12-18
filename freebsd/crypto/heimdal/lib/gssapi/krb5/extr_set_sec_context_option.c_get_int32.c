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
struct TYPE_3__ {int length; int /*<<< orphan*/  value; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_UNAVAILABLE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static OM_uint32
get_int32(OM_uint32 *minor_status,
	  const gss_buffer_t value,
	  OM_uint32 *ret)
{
    *minor_status = 0;
    if (value == NULL || value->length == 0)
	*ret = 0;
    else if (value->length == sizeof(*ret))
	memcpy(ret, value->value, sizeof(*ret));
    else
	return GSS_S_UNAVAILABLE;

    return GSS_S_COMPLETE;
}