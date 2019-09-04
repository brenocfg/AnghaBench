#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  interrupt_callback; TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_9__ {scalar_t__ io_manager_ctx; } ;
struct TYPE_8__ {TYPE_3__* cur_ffmpeg_ctx; int /*<<< orphan*/ * ijkio_interrupt_callback; } ;
typedef  TYPE_2__ IjkIOManagerContext ;
typedef  int /*<<< orphan*/  IjkAVIOInterruptCB ;
typedef  int /*<<< orphan*/  IjkAVDictionary ;
typedef  TYPE_3__ Context ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  av_strstart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  ijk_av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ijkio_copy_options (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ijkio_manager_io_close (TYPE_2__*) ; 
 int ijkio_manager_io_open (TYPE_2__*,char const*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int ijkio_open(URLContext *h, const char *arg, int flags, AVDictionary **options)
{
    Context *c = h->priv_data;
    int ret = -1;

    if (!c || !c->io_manager_ctx)
        return -1;

    IjkIOManagerContext *manager_ctx = (IjkIOManagerContext *)(c->io_manager_ctx);
    manager_ctx->ijkio_interrupt_callback = (IjkAVIOInterruptCB *)&(h->interrupt_callback);

    av_strstart(arg, "ijkio:", &arg);
    IjkAVDictionary *opts = NULL;
    ijkio_copy_options(&opts, *options);

    manager_ctx->cur_ffmpeg_ctx = c;

    ret = ijkio_manager_io_open(manager_ctx, arg, flags, &opts);
    ijk_av_dict_free(&opts);

    if (ret != 0) {
        ijkio_manager_io_close(manager_ctx);
    }

    return ret;
}