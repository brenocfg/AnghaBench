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
struct TYPE_7__ {int /*<<< orphan*/  inner; } ;
struct TYPE_6__ {TYPE_1__* ijkio_app_ctx; TYPE_3__* priv_data; } ;
struct TYPE_5__ {scalar_t__ ijkio_interrupt_callback; } ;
typedef  TYPE_2__ IjkURLContext ;
typedef  TYPE_3__ IjkIOFFioContext ;
typedef  int /*<<< orphan*/  IjkAVDictionary ;
typedef  int /*<<< orphan*/  AVIOInterruptCB ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_strstart (char const*,char*,char const**) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ijkio_copy_options (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ijkio_ffio_open(IjkURLContext *h, const char *url, int flags, IjkAVDictionary **options) {
    int ret = -1;

    IjkIOFFioContext *c= h->priv_data;
    if (!c)
        return -1;

    AVDictionary *opts = NULL;
    ijkio_copy_options(&opts, *options);

    av_strstart(url, "ffio:", &url);
    if (h->ijkio_app_ctx) {
        ret = ffurl_open_whitelist(&c->inner, url, flags, (AVIOInterruptCB *)h->ijkio_app_ctx->ijkio_interrupt_callback,
                                &opts, NULL, NULL, NULL);
    } else {
        ret = -1;
    }

    av_dict_free(&opts);

    return ret;
}