#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct _citrus_mapper {scalar_t__ cm_refcount; int /*<<< orphan*/  cm_key; } ;

/* Variables and functions */
 scalar_t__ REFCOUNT_PERSISTENT ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CITRUS_HASH_REMOVE (struct _citrus_mapper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_entry ; 
 int /*<<< orphan*/  cm_lock ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapper_close (struct _citrus_mapper*) ; 

void
_citrus_mapper_close(struct _citrus_mapper *cm)
{

	if (cm) {
		WLOCK(&cm_lock);
		if (cm->cm_refcount == REFCOUNT_PERSISTENT)
			goto quit;
		if (cm->cm_refcount > 0) {
			if (--cm->cm_refcount > 0)
				goto quit;
			_CITRUS_HASH_REMOVE(cm, cm_entry);
			free(cm->cm_key);
		}
		UNLOCK(&cm_lock);
		mapper_close(cm);
		return;
quit:
		UNLOCK(&cm_lock);
	}
}