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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ gss_iov_buffer_desc ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_IOV_BUFFER_TYPE (int /*<<< orphan*/ ) ; 

gss_iov_buffer_desc *
_gk_find_buffer(gss_iov_buffer_desc *iov, int iov_count, OM_uint32 type)
{
    int i;

    for (i = 0; i < iov_count; i++)
	if (type == GSS_IOV_BUFFER_TYPE(iov[i].type))
	    return &iov[i];
    return NULL;
}