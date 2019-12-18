#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {scalar_t__ logical_pos; scalar_t__ logical_size; int io_error; } ;
typedef  TYPE_2__ Context ;

/* Variables and functions */
 scalar_t__ AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
 int ijkhttphook_reconnect_at (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ijkurlhook_seek (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static int64_t ijkhttphook_reseek_at(URLContext *h, int64_t pos, int whence, int force_reconnect)
{
    Context *c = h->priv_data;
    int ret = 0;

    if (!force_reconnect)
        return ijkurlhook_seek(h, pos, whence);

    if (whence == SEEK_CUR)
        pos += c->logical_pos;
    else if (whence == SEEK_END)
        pos += c->logical_size;
    else if (whence != SEEK_SET)
        return AVERROR(EINVAL);
    if (pos < 0)
        return AVERROR(EINVAL);

    ret = ijkhttphook_reconnect_at(h, pos);
    if (ret) {
        c->io_error = ret;
        return ret;
    }

    c->io_error = 0;
    return c->logical_pos;
}