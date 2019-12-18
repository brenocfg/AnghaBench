#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * swr_opts; int /*<<< orphan*/ * player_opts; int /*<<< orphan*/ * sws_dict; int /*<<< orphan*/ * codec_opts; int /*<<< orphan*/ * format_opts; } ;
typedef  TYPE_1__ FFPlayer ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  FFP_OPT_CATEGORY_CODEC 132 
#define  FFP_OPT_CATEGORY_FORMAT 131 
#define  FFP_OPT_CATEGORY_PLAYER 130 
#define  FFP_OPT_CATEGORY_SWR 129 
#define  FFP_OPT_CATEGORY_SWS 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static AVDictionary **ffp_get_opt_dict(FFPlayer *ffp, int opt_category)
{
    assert(ffp);

    switch (opt_category) {
        case FFP_OPT_CATEGORY_FORMAT:   return &ffp->format_opts;
        case FFP_OPT_CATEGORY_CODEC:    return &ffp->codec_opts;
        case FFP_OPT_CATEGORY_SWS:      return &ffp->sws_dict;
        case FFP_OPT_CATEGORY_PLAYER:   return &ffp->player_opts;
        case FFP_OPT_CATEGORY_SWR:      return &ffp->swr_opts;
        default:
            av_log(ffp, AV_LOG_ERROR, "unknown option category %d\n", opt_category);
            return NULL;
    }
}