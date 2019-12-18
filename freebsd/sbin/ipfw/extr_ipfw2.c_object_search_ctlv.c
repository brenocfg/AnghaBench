#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct object_kt {void* type; void* uidx; } ;
struct TYPE_6__ {char* name; } ;
typedef  TYPE_1__ ipfw_obj_ntlv ;
struct TYPE_7__ {int /*<<< orphan*/  objsize; int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ ipfw_obj_ctlv ;

/* Variables and functions */
 TYPE_1__* bsearch (struct object_kt*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_object_kntlv ; 

__attribute__((used)) static char *
object_search_ctlv(ipfw_obj_ctlv *ctlv, uint16_t idx, uint16_t type)
{
	ipfw_obj_ntlv *ntlv;
	struct object_kt key;

	key.uidx = idx;
	key.type = type;

	ntlv = bsearch(&key, (ctlv + 1), ctlv->count, ctlv->objsize,
	    compare_object_kntlv);

	if (ntlv != NULL)
		return (ntlv->name);

	return (NULL);
}