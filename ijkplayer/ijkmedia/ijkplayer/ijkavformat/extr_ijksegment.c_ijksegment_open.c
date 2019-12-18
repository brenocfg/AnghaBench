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
typedef  int /*<<< orphan*/  io_control ;
struct TYPE_7__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_9__ {int size; int segment_index; int /*<<< orphan*/ * url; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int app_ctx_intptr; int /*<<< orphan*/  inner; } ;
typedef  TYPE_2__ Context ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  AVApplicationContext ;
typedef  TYPE_3__ AVAppIOControl ;

/* Variables and functions */
 int /*<<< orphan*/  AVAPP_CTRL_WILL_CONCAT_SEGMENT_OPEN ; 
 int AVERROR_EXIT ; 
 int AVERROR_EXTERNAL ; 
 int av_application_on_io_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strstart (char const*,char*,char const**) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ijksegment_open(URLContext *h, const char *arg, int flags, AVDictionary **options)
{
    Context *c = h->priv_data;
    AVAppIOControl io_control = {0};
    AVApplicationContext *app_ctx = (AVApplicationContext *)(intptr_t)c->app_ctx_intptr;
    int ret = -1;
    int segment_index = -1;

    av_strstart(arg, "ijksegment:", &arg);

    if (!arg || !*arg)
        return AVERROR_EXTERNAL;

    segment_index = (int)strtol(arg, NULL, 0);
    io_control.size = sizeof(io_control);
    io_control.segment_index = segment_index;
    strlcpy(io_control.url,    arg,    sizeof(io_control.url));

    if (app_ctx && io_control.segment_index < 0) {
        ret = AVERROR_EXTERNAL;
        goto fail;
    }
    ret = av_application_on_io_control(app_ctx, AVAPP_CTRL_WILL_CONCAT_SEGMENT_OPEN, &io_control);
    if (ret || !io_control.url[0]) {
        ret = AVERROR_EXIT;
        goto fail;
    }

    av_dict_set_int(options, "ijkapplication", c->app_ctx_intptr, 0);
    av_dict_set_int(options, "ijkinject-segment-index", segment_index, 0);

    ret = ffurl_open_whitelist(&c->inner,
                               io_control.url,
                               flags,
                               &h->interrupt_callback,
                               options,
                               h->protocol_whitelist,
                               h->protocol_blacklist,
                               h);
    if (ret)
        goto fail;

    return 0;
fail:
    return ret;
}