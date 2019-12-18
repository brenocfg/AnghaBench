#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {scalar_t__ st_mtime; scalar_t__ st_size; } ;
struct TYPE_7__ {int fd; TYPE_2__ _etag; TYPE_1__ st; } ;
typedef  TYPE_3__ h2o_filecache_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sprintf (int /*<<< orphan*/ ,char*,unsigned int,size_t) ; 

size_t h2o_filecache_get_etag(h2o_filecache_ref_t *ref, char *outbuf)
{
    assert(ref->fd != -1);
    if (ref->_etag.len == 0)
        ref->_etag.len = sprintf(ref->_etag.buf, "\"%08x-%zx\"", (unsigned)ref->st.st_mtime, (size_t)ref->st.st_size);
    memcpy(outbuf, ref->_etag.buf, ref->_etag.len + 1);
    return ref->_etag.len;
}