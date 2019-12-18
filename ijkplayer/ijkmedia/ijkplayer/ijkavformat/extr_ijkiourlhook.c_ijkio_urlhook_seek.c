#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {TYPE_1__* prot; } ;
struct TYPE_8__ {int io_error; scalar_t__ test_fail_point; scalar_t__ logical_pos; scalar_t__ test_fail_point_next; TYPE_4__* inner; } ;
struct TYPE_7__ {TYPE_3__* priv_data; } ;
struct TYPE_6__ {scalar_t__ (* url_seek ) (TYPE_4__*,scalar_t__,int) ;} ;
typedef  TYPE_2__ IjkURLContext ;
typedef  TYPE_3__ Context ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_4__*,scalar_t__,int) ; 

__attribute__((used)) static int64_t ijkio_urlhook_seek(IjkURLContext *h, int64_t pos, int whence)
{
    Context *c = h->priv_data;
    int64_t seek_ret = 0;

    seek_ret = c->inner->prot->url_seek(c->inner, pos, whence);
    if (seek_ret < 0) {
        c->io_error = (int)seek_ret;
        return seek_ret;
    }

    c->logical_pos = seek_ret;
    if (c->test_fail_point)
        c->test_fail_point_next = c->logical_pos + c->test_fail_point;

    c->io_error = 0;
    return seek_ret;
}