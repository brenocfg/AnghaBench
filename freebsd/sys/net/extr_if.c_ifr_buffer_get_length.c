#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t length; } ;
struct TYPE_11__ {TYPE_4__ ifru_buffer; } ;
struct TYPE_12__ {TYPE_5__ ifr_ifru; } ;
struct TYPE_7__ {size_t length; } ;
struct TYPE_8__ {TYPE_1__ ifru_buffer; } ;
struct TYPE_9__ {TYPE_2__ ifr_ifru; } ;
union ifreq_union {TYPE_6__ ifr; TYPE_3__ ifr32; } ;

/* Variables and functions */
 scalar_t__ SV_CURPROC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_ILP32 ; 

__attribute__((used)) static size_t
ifr_buffer_get_length(void *data)
{
	union ifreq_union *ifrup;

	ifrup = data;
#ifdef COMPAT_FREEBSD32
	if (SV_CURPROC_FLAG(SV_ILP32))
		return (ifrup->ifr32.ifr_ifru.ifru_buffer.length);
#endif
	return (ifrup->ifr.ifr_ifru.ifru_buffer.length);
}