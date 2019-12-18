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
typedef  int /*<<< orphan*/  set ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_3__ {int length; int /*<<< orphan*/  value; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_UNAVAILABLE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static OM_uint32
set_int32(OM_uint32 *minor_status,
	  const gss_buffer_t value,
	  OM_uint32 set)
{
    *minor_status = 0;
    if (value->length == sizeof(set))
	memcpy(value->value, &set, sizeof(set));
    else
	return GSS_S_UNAVAILABLE;

    return GSS_S_COMPLETE;
}