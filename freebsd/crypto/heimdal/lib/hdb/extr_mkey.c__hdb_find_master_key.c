#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_2__* hdb_master_key ;
struct TYPE_5__ {scalar_t__ vno; } ;
struct TYPE_6__ {struct TYPE_6__* next; TYPE_1__ keytab; } ;

/* Variables and functions */

hdb_master_key
_hdb_find_master_key(uint32_t *mkvno, hdb_master_key mkey)
{
    hdb_master_key ret = NULL;
    while(mkey) {
	if(ret == NULL && mkey->keytab.vno == 0)
	    ret = mkey;
	if(mkvno == NULL) {
	    if(ret == NULL || mkey->keytab.vno > ret->keytab.vno)
		ret = mkey;
	} else if((uint32_t)mkey->keytab.vno == *mkvno)
	    return mkey;
	mkey = mkey->next;
    }
    return ret;
}