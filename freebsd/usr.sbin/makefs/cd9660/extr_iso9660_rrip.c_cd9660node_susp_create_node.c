#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* type; } ;
struct TYPE_6__ {TYPE_1__ h; } ;
struct TYPE_7__ {TYPE_2__ SP; } ;
struct TYPE_8__ {TYPE_3__ su_entry; } ;
struct ISO_SUSP_ATTRIBUTES {int susp_type; int entry_type; char* type_of; int write_location; TYPE_4__ attr; scalar_t__ last_in_suf; } ;

/* Variables and functions */
 struct ISO_SUSP_ATTRIBUTES* emalloc (int) ; 

struct ISO_SUSP_ATTRIBUTES*
cd9660node_susp_create_node(int susp_type, int entry_type, const char *type_id,
			    int write_loc)
{
	struct ISO_SUSP_ATTRIBUTES* temp;

	temp = emalloc(sizeof(*temp));
	temp->susp_type = susp_type;
	temp->entry_type = entry_type;
	temp->last_in_suf = 0;
	/* Phase this out */
	temp->type_of[0] = type_id[0];
	temp->type_of[1] = type_id[1];
	temp->write_location = write_loc;

	/*
	 * Since the first four bytes is common, lets go ahead and
	 * set the type identifier, since we are passing that to this
	 * function anyhow.
	 */
	temp->attr.su_entry.SP.h.type[0] = type_id[0];
	temp->attr.su_entry.SP.h.type[1] = type_id[1];
	return temp;
}