#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int hash; } ;
struct key_entry_key {TYPE_1__ entry; int /*<<< orphan*/  name; int /*<<< orphan*/  key_class; } ;

/* Variables and functions */
 int dname_query_hash (int /*<<< orphan*/ ,int) ; 
 int hashlittle (int /*<<< orphan*/ *,int,int) ; 

void 
key_entry_hash(struct key_entry_key* kk)
{
	kk->entry.hash = 0x654;
	kk->entry.hash = hashlittle(&kk->key_class, sizeof(kk->key_class), 
		kk->entry.hash);
	kk->entry.hash = dname_query_hash(kk->name, kk->entry.hash);
}