#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* priv_data; TYPE_1__* prot; } ;
struct TYPE_9__ {TYPE_4__* inner; scalar_t__ inner_options; } ;
struct TYPE_8__ {TYPE_3__* priv_data; } ;
struct TYPE_7__ {int (* url_close ) (TYPE_4__*) ;} ;
typedef  TYPE_2__ IjkURLContext ;
typedef  TYPE_3__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int IJKAVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijk_av_dict_free (scalar_t__*) ; 
 int /*<<< orphan*/  ijk_av_freep (TYPE_4__**) ; 
 int stub1 (TYPE_4__*) ; 

__attribute__((used)) static int ijkio_httphook_close(IjkURLContext *h)
{
    Context *c = h->priv_data;
    int ret = 0;
    if (!c || !c->inner || !c->inner->prot)
        return IJKAVERROR(ENOSYS);

    ret = c->inner->prot->url_close(c->inner);
    if (c->inner_options) {
        ijk_av_dict_free(&c->inner_options);
    }
    ijk_av_freep(&c->inner->priv_data);
    ijk_av_freep(&c->inner);

    return ret;
}