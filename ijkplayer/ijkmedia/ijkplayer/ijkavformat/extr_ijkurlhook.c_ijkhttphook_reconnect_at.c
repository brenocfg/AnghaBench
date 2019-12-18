#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int64_t ;
typedef  int /*<<< orphan*/  URLContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ ) ; 
 int ijkurlhook_reconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ijkhttphook_reconnect_at(URLContext *h, int64_t offset)
{
    int           ret        = 0;
    AVDictionary *extra_opts = NULL;

    av_dict_set_int(&extra_opts, "offset", offset, 0);
    av_dict_set_int(&extra_opts, "dns_cache_clear", 1, 0);
    ret = ijkurlhook_reconnect(h, extra_opts);
    av_dict_free(&extra_opts);
    return ret;
}