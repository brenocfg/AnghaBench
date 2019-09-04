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
struct TYPE_6__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {char* scheme; char* inner_scheme; scalar_t__ app_ctx_intptr; int /*<<< orphan*/ * app_ctx; } ;
typedef  TYPE_2__ Context ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  AVApplicationContext ;

/* Variables and functions */
 int ijkurlhook_init (TYPE_1__*,char const*,int,int /*<<< orphan*/ **) ; 
 int ijkurlhook_reconnect (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ijktcphook_open(URLContext *h, const char *arg, int flags, AVDictionary **options)
{
    Context *c = h->priv_data;
    int ret = 0;

    c->app_ctx = (AVApplicationContext *)(intptr_t)c->app_ctx_intptr;
    c->scheme = "ijktcphook:";
    c->inner_scheme = "tcp:";
    ret = ijkurlhook_init(h, arg, flags, options);
    if (ret)
        goto fail;

    ret = ijkurlhook_reconnect(h, NULL);
    if (ret)
        goto fail;

fail:
    return ret;
}