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
typedef  scalar_t__ uint16_t ;
struct tidx {int count; scalar_t__ set; int size; scalar_t__ counter; TYPE_2__* idx; } ;
struct TYPE_6__ {int type; int length; } ;
struct TYPE_7__ {scalar_t__ set; scalar_t__ idx; TYPE_1__ head; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ipfw_obj_ntlv ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* realloc (TYPE_2__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static uint16_t
pack_object(struct tidx *tstate, char *name, int otype)
{
	int i;
	ipfw_obj_ntlv *ntlv;

	for (i = 0; i < tstate->count; i++) {
		if (strcmp(tstate->idx[i].name, name) != 0)
			continue;
		if (tstate->idx[i].set != tstate->set)
			continue;
		if (tstate->idx[i].head.type != otype)
			continue;

		return (tstate->idx[i].idx);
	}

	if (tstate->count + 1 > tstate->size) {
		tstate->size += 4;
		tstate->idx = realloc(tstate->idx, tstate->size *
		    sizeof(ipfw_obj_ntlv));
		if (tstate->idx == NULL)
			return (0);
	}

	ntlv = &tstate->idx[i];
	memset(ntlv, 0, sizeof(ipfw_obj_ntlv));
	strlcpy(ntlv->name, name, sizeof(ntlv->name));
	ntlv->head.type = otype;
	ntlv->head.length = sizeof(ipfw_obj_ntlv);
	ntlv->set = tstate->set;
	ntlv->idx = ++tstate->counter;
	tstate->count++;

	return (ntlv->idx);
}