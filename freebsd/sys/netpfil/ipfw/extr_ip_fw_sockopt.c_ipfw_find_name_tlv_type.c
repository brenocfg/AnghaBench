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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int length; scalar_t__ type; } ;
struct TYPE_5__ {scalar_t__ idx; int /*<<< orphan*/  name; TYPE_1__ head; } ;
typedef  TYPE_2__ ipfw_obj_ntlv ;

/* Variables and functions */
 scalar_t__ ipfw_check_object_name_generic (int /*<<< orphan*/ ) ; 

ipfw_obj_ntlv *
ipfw_find_name_tlv_type(void *tlvs, int len, uint16_t uidx, uint32_t etlv)
{
	ipfw_obj_ntlv *ntlv;
	uintptr_t pa, pe;
	int l;

	pa = (uintptr_t)tlvs;
	pe = pa + len;
	l = 0;
	for (; pa < pe; pa += l) {
		ntlv = (ipfw_obj_ntlv *)pa;
		l = ntlv->head.length;

		if (l != sizeof(*ntlv))
			return (NULL);

		if (ntlv->idx != uidx)
			continue;
		/*
		 * When userland has specified zero TLV type, do
		 * not compare it with eltv. In some cases userland
		 * doesn't know what type should it have. Use only
		 * uidx and name for search named_object.
		 */
		if (ntlv->head.type != 0 &&
		    ntlv->head.type != (uint16_t)etlv)
			continue;

		if (ipfw_check_object_name_generic(ntlv->name) != 0)
			return (NULL);

		return (ntlv);
	}

	return (NULL);
}