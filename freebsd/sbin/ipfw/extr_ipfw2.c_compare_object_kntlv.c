#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object_kt {scalar_t__ uidx; scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {scalar_t__ idx; TYPE_1__ head; } ;
typedef  TYPE_2__ ipfw_obj_ntlv ;

/* Variables and functions */

__attribute__((used)) static int
compare_object_kntlv(const void *k, const void *v)
{
	ipfw_obj_ntlv *ntlv;
	struct object_kt key;

	key = *((struct object_kt *)k);
	ntlv = (ipfw_obj_ntlv *)v;

	if (key.uidx < ntlv->idx)
		return (-1);
	else if (key.uidx > ntlv->idx)
		return (1);

	if (key.type < ntlv->head.type)
		return (-1);
	else if (key.type > ntlv->head.type)
		return (1);

	return (0);
}