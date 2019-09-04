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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  FFPlayer ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** ffp_get_opt_dict (int /*<<< orphan*/ *,int) ; 

void ffp_set_option_int(FFPlayer *ffp, int opt_category, const char *name, int64_t value)
{
    if (!ffp)
        return;

    AVDictionary **dict = ffp_get_opt_dict(ffp, opt_category);
    av_dict_set_int(dict, name, value, 0);
}