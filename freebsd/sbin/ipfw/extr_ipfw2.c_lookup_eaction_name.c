#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/  idx; TYPE_1__ head; } ;
typedef  TYPE_2__ ipfw_obj_ntlv ;

/* Variables and functions */
 scalar_t__ IPFW_TLV_EACTION ; 
 scalar_t__ IPFW_TLV_EACTION_NAME (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*
lookup_eaction_name(ipfw_obj_ntlv *ntlv, int cnt, uint16_t type)
{
	const char *name;
	int i;

	name = NULL;
	for (i = 0; i < cnt; i++) {
		if (ntlv[i].head.type != IPFW_TLV_EACTION)
			continue;
		if (IPFW_TLV_EACTION_NAME(ntlv[i].idx) != type)
			continue;
		name = ntlv[i].name;
		break;
	}
	return (name);
}