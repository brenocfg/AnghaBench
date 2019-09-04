#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dict; } ;
typedef  TYPE_1__ IjkMediaMeta ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 

void ijkmeta_set_string_l(IjkMediaMeta *meta, const char *name, const char *value)
{
    if (!meta)
        return;

    av_dict_set(&meta->dict, name, value, 0);
}