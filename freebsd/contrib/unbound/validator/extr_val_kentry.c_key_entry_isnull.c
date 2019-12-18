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
struct TYPE_2__ {scalar_t__ data; } ;
struct key_entry_key {TYPE_1__ entry; } ;
struct key_entry_data {int /*<<< orphan*/ * rrset_data; int /*<<< orphan*/  isbad; } ;

/* Variables and functions */

int 
key_entry_isnull(struct key_entry_key* kkey)
{
	struct key_entry_data* d = (struct key_entry_data*)kkey->entry.data;
	return (!d->isbad && d->rrset_data == NULL);
}