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
typedef  int /*<<< orphan*/  IjkURLContext ;
typedef  int /*<<< orphan*/  IjkAVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  ijk_av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ijk_av_dict_set_int (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ ) ; 
 int ijkio_urlhook_reconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ijkio_httphook_reconnect_at(IjkURLContext *h, int64_t offset)
{
    int ret = 0;
    IjkAVDictionary *extra_opts = NULL;

    ijk_av_dict_set_int(&extra_opts, "offset", offset, 0);
    ijk_av_dict_set_int(&extra_opts, "dns_cache_clear", 1, 0);
    ret = ijkio_urlhook_reconnect(h, extra_opts);
    ijk_av_dict_free(&extra_opts);
    return ret;
}