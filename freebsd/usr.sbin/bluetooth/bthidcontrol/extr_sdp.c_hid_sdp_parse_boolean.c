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
typedef  TYPE_1__* sdp_attr_p ;
typedef  int int32_t ;
struct TYPE_3__ {int vlen; scalar_t__* value; } ;

/* Variables and functions */
 scalar_t__ SDP_DATA_BOOL ; 

__attribute__((used)) static int32_t
hid_sdp_parse_boolean(sdp_attr_p a)
{
	if (a->vlen != 2 || a->value[0] != SDP_DATA_BOOL)
		return (-1);

	return (a->value[1]);
}