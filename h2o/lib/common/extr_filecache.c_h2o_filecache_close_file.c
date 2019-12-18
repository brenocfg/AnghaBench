#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ _refcnt; int fd; int /*<<< orphan*/  _lru; } ;
typedef  TYPE_1__ h2o_filecache_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 

void h2o_filecache_close_file(h2o_filecache_ref_t *ref)
{
    if (--ref->_refcnt != 0)
        return;
    assert(!h2o_linklist_is_linked(&ref->_lru));
    if (ref->fd != -1) {
        close(ref->fd);
        ref->fd = -1;
    }
    free(ref);
}