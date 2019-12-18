#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int io_error; scalar_t__ test_fail_point; scalar_t__ logical_pos; scalar_t__ test_fail_point_next; int /*<<< orphan*/  inner; } ;
typedef  TYPE_2__ Context ;

/* Variables and functions */
 scalar_t__ ffurl_seek (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int64_t ijkurlhook_seek(URLContext *h, int64_t pos, int whence)
{
    Context *c = h->priv_data;
    int64_t seek_ret = 0;

    seek_ret = ffurl_seek(c->inner, pos, whence);
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