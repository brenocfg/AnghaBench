#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  is_streamed; int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_15__ {int /*<<< orphan*/  is_streamed; } ;
struct TYPE_14__ {TYPE_1__* opaque; int /*<<< orphan*/  callback; } ;
struct TYPE_13__ {int /*<<< orphan*/  ring; TYPE_5__* inner; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond_wakeup_main; int /*<<< orphan*/  cond_wakeup_background; int /*<<< orphan*/  async_buffer_thread; int /*<<< orphan*/  logical_size; int /*<<< orphan*/  interrupt_callback; scalar_t__ app_ctx_intptr; int /*<<< orphan*/ * app_ctx; int /*<<< orphan*/  backwards_capacity; int /*<<< orphan*/  forwards_capacity; } ;
typedef  TYPE_2__ Context ;
typedef  TYPE_3__ AVIOInterruptCB ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  AVApplicationContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  async_buffer_task ; 
 int /*<<< orphan*/  async_check_interrupt ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  av_strstart (char const*,char*,char const**) ; 
 int /*<<< orphan*/  ffurl_close (TYPE_5__*) ; 
 int ffurl_open_whitelist (TYPE_5__**,char const*,int,TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ffurl_size (TYPE_5__*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_destroy (int /*<<< orphan*/ *) ; 
 int ring_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int async_open(URLContext *h, const char *arg, int flags, AVDictionary **options)
{
    Context         *c = h->priv_data;
    int              ret;
    AVIOInterruptCB  interrupt_callback = {.callback = async_check_interrupt, .opaque = h};

    av_strstart(arg, "async:", &arg);

    ret = ring_init(&c->ring, c->forwards_capacity, c->backwards_capacity);
    if (ret < 0)
        goto fifo_fail;

    if (c->app_ctx_intptr) {
        c->app_ctx = (AVApplicationContext *)(intptr_t)c->app_ctx_intptr;
        av_dict_set_int(options, "ijkapplication", c->app_ctx_intptr, 0);
    }
    /* wrap interrupt callback */
    c->interrupt_callback = h->interrupt_callback;
    ret = ffurl_open_whitelist(&c->inner, arg, flags, &interrupt_callback, options, h->protocol_whitelist, h->protocol_blacklist, h);
    if (ret != 0) {
        av_log(h, AV_LOG_ERROR, "ffurl_open_whitelist failed : %s, %s\n", av_err2str(ret), arg);
        goto url_fail;
    }

    c->logical_size = ffurl_size(c->inner);
    h->is_streamed  = c->inner->is_streamed;

    ret = pthread_mutex_init(&c->mutex, NULL);
    if (ret != 0) {
        av_log(h, AV_LOG_ERROR, "pthread_mutex_init failed : %s\n", av_err2str(ret));
        goto mutex_fail;
    }

    ret = pthread_cond_init(&c->cond_wakeup_main, NULL);
    if (ret != 0) {
        av_log(h, AV_LOG_ERROR, "pthread_cond_init failed : %s\n", av_err2str(ret));
        goto cond_wakeup_main_fail;
    }

    ret = pthread_cond_init(&c->cond_wakeup_background, NULL);
    if (ret != 0) {
        av_log(h, AV_LOG_ERROR, "pthread_cond_init failed : %s\n", av_err2str(ret));
        goto cond_wakeup_background_fail;
    }

    ret = pthread_create(&c->async_buffer_thread, NULL, async_buffer_task, h);
    if (ret) {
        av_log(h, AV_LOG_ERROR, "pthread_create failed : %s\n", av_err2str(ret));
        goto thread_fail;
    }

    return 0;

thread_fail:
    pthread_cond_destroy(&c->cond_wakeup_background);
cond_wakeup_background_fail:
    pthread_cond_destroy(&c->cond_wakeup_main);
cond_wakeup_main_fail:
    pthread_mutex_destroy(&c->mutex);
mutex_fail:
    ffurl_close(c->inner);
url_fail:
    ring_destroy(&c->ring);
fifo_fail:
    return ret;
}