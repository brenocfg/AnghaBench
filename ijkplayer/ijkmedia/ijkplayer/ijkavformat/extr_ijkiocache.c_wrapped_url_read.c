#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* prot; } ;
struct TYPE_8__ {int* cache_count_bytes; int inner_io_error; TYPE_5__* inner; } ;
struct TYPE_7__ {TYPE_3__* priv_data; } ;
struct TYPE_6__ {int (* url_read ) (TYPE_5__*,void*,int) ;} ;
typedef  TYPE_2__ IjkURLContext ;
typedef  TYPE_3__ IjkIOCacheContext ;

/* Variables and functions */
 int stub1 (TYPE_5__*,void*,int) ; 

__attribute__((used)) static int wrapped_url_read(IjkURLContext *h, void *dst, int size)
{
    IjkIOCacheContext *c   = h->priv_data;
    int ret;

    ret = c->inner->prot->url_read(c->inner, dst, size);

    if (ret > 0)
        *c->cache_count_bytes += ret;

    c->inner_io_error = ret < 0 ? ret : 0;

    return ret;
}