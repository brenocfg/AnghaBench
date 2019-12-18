#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_11__ {size_t len; TYPE_5__* val; } ;
struct TYPE_14__ {TYPE_3__ keys; } ;
struct TYPE_12__ {TYPE_8__ entry; int /*<<< orphan*/  (* free_entry ) (int /*<<< orphan*/ ,TYPE_4__*) ;} ;
typedef  TYPE_4__ hdb_entry_ex ;
struct TYPE_9__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__ keyvalue; } ;
struct TYPE_13__ {TYPE_2__ key; } ;
typedef  TYPE_5__ Key ;

/* Variables and functions */
 int /*<<< orphan*/  free_hdb_entry (TYPE_8__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 

void
hdb_free_entry(krb5_context context, hdb_entry_ex *ent)
{
    size_t i;

    if (ent->free_entry)
	(*ent->free_entry)(context, ent);

    for(i = 0; i < ent->entry.keys.len; ++i) {
	Key *k = &ent->entry.keys.val[i];

	memset (k->key.keyvalue.data, 0, k->key.keyvalue.length);
    }
    free_hdb_entry(&ent->entry);
}