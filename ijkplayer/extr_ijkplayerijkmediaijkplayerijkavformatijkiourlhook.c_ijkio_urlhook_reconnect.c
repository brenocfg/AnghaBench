#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  url; } ;
struct TYPE_14__ {struct TYPE_14__* priv_data; scalar_t__ io_error; struct TYPE_14__* inner; TYPE_2__* prot; int /*<<< orphan*/  logical_size; int /*<<< orphan*/  logical_pos; int /*<<< orphan*/  inner_flags; TYPE_1__ app_io_ctrl; int /*<<< orphan*/  ijkio_app_ctx; int /*<<< orphan*/ * inner_options; scalar_t__ test_fail_point; int /*<<< orphan*/  test_fail_point_next; } ;
struct TYPE_13__ {int (* url_open2 ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;int /*<<< orphan*/  (* url_seek ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* url_close ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ IjkURLContext ;
typedef  int /*<<< orphan*/  IjkAVDictionary ;
typedef  TYPE_3__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  IJKAVSEEK_SIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ijk_av_dict_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijk_av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ijk_av_freep (TYPE_3__**) ; 
 int ijkio_alloc_url (TYPE_3__**,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ijkio_urlhook_reconnect(IjkURLContext *h, IjkAVDictionary *extra)
{
    Context *c = h->priv_data;
    int ret = 0;
    IjkURLContext *new_url = NULL;
    IjkAVDictionary *inner_options = NULL;

    c->test_fail_point_next += c->test_fail_point;

    assert(c->inner_options);
    ijk_av_dict_copy(&inner_options, c->inner_options, 0);
    if (extra)
        ijk_av_dict_copy(&inner_options, extra, 0);

    ret = ijkio_alloc_url(&new_url, c->app_io_ctrl.url);
    new_url->ijkio_app_ctx = c->ijkio_app_ctx;
    if (ret)
        goto fail0;

    ret = new_url->prot->url_open2(new_url, c->app_io_ctrl.url, c->inner_flags, &inner_options);
    if (ret)
        goto fail1;

    if (c->inner) {
        c->inner->prot->url_close(c->inner);
        ijk_av_freep(&c->inner->priv_data);
        ijk_av_freep(&c->inner);
    }

    c->inner        = new_url;
    c->logical_pos  = c->inner->prot->url_seek(c->inner, 0, SEEK_CUR);
    c->logical_size = c->inner->prot->url_seek(c->inner, 0, IJKAVSEEK_SIZE);
    c->io_error     = 0;
    if (inner_options) {
        ijk_av_dict_free(&inner_options);
    }
    return ret;

fail1:
    ijk_av_freep(&new_url->priv_data);
    ijk_av_freep(&new_url);
fail0:
    if (inner_options) {
        ijk_av_dict_free(&inner_options);
    }
    return ret;
}