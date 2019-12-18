#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;
struct TYPE_3__ {int max_elem; int lockcreated; int /*<<< orphan*/  lock; int /*<<< orphan*/ * elem_array; } ;
typedef  TYPE_1__ pqi_taglist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  os_mem_free (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  os_uninit_spinlock (int /*<<< orphan*/ *) ; 

void pqisrc_destroy_taglist(pqisrc_softstate_t *softs, pqi_taglist_t *taglist)
{
	DBG_FUNC("IN\n");
	os_mem_free(softs, (char *)taglist->elem_array, 
		(taglist->max_elem * sizeof(uint32_t)));
	taglist->elem_array = NULL;
    
    	if(taglist->lockcreated==true){
        	os_uninit_spinlock(&taglist->lock);
        	taglist->lockcreated = false;
    	}
    
	DBG_FUNC("OUT\n");
}