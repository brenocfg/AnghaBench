#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  dict; } ;
typedef  TYPE_1__ IjkMediaMeta ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int /*<<< orphan*/  atoll (int /*<<< orphan*/ ) ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int64_t ijkmeta_get_int64_l(IjkMediaMeta *meta, const char *name, int64_t defaultValue)
{
    if (!meta || !meta->dict)
        return defaultValue;

    AVDictionaryEntry *entry = av_dict_get(meta->dict, name, NULL, 0);
    if (!entry || !entry->value)
        return defaultValue;

    return atoll(entry->value);
}