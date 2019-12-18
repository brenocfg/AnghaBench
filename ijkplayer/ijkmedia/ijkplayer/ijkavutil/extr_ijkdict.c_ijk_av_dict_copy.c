#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ IjkAVDictionaryEntry ;
typedef  int /*<<< orphan*/  IjkAVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  IJK_AV_DICT_IGNORE_SUFFIX ; 
 TYPE_1__* ijk_av_dict_get (int /*<<< orphan*/  const*,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ijk_av_dict_set (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ijk_av_dict_copy(IjkAVDictionary **dst, const IjkAVDictionary *src, int flags)
{
    IjkAVDictionaryEntry *t = NULL;

    while ((t = ijk_av_dict_get(src, "", t, IJK_AV_DICT_IGNORE_SUFFIX))) {
        int ret = ijk_av_dict_set(dst, t->key, t->value, flags);
        if (ret < 0)
            return ret;
    }

    return 0;
}