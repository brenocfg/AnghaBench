#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gr ;
typedef  int __itt_group_id ;
struct TYPE_4__ {char const* env_var; int groups; } ;
struct TYPE_3__ {int id; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 char* __itt_fsplit (char const*,char*,char const**,int*) ; 
 int /*<<< orphan*/  __itt_fstrcmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __itt_fstrcpyn (char*,int,char const*,int) ; 
 char* __itt_get_env_var (char const*) ; 
 int __itt_group_all ; 
 int __itt_group_none ; 
 int __itt_group_splitter_max ; 
 int __itt_group_splitter_min ; 
 int __itt_min (int,int) ; 
 TYPE_2__* group_alias ; 
 TYPE_1__* group_list ; 

__attribute__((used)) static __itt_group_id __itt_get_groups(void)
{
    int i;
    __itt_group_id res = __itt_group_none;
    const char* var_name  = "INTEL_ITTNOTIFY_GROUPS";
    const char* group_str = __itt_get_env_var(var_name);

    if (group_str != NULL)
    {
        int len;
        char gr[255];
        const char* chunk;
        while ((group_str = __itt_fsplit(group_str, ",; ", &chunk, &len)) != NULL)
        {
            int min_len = __itt_min(len, (int)(sizeof(gr) - 1));
            __itt_fstrcpyn(gr, sizeof(gr) - 1, chunk,  min_len);
            gr[min_len] = 0;

            for (i = 0; group_list[i].name != NULL; i++)
            {
                if (!__itt_fstrcmp(gr, group_list[i].name))
                {
                    res = (__itt_group_id)(res | group_list[i].id);
                    break;
                }
            }
        }
        /* TODO: !!! Workaround for bug with warning for unknown group !!!
         * Should be fixed in new initialization scheme.
         * Now the following groups should be set always. */
        for (i = 0; group_list[i].id != __itt_group_none; i++)
            if (group_list[i].id != __itt_group_all &&
                group_list[i].id > __itt_group_splitter_min &&
                group_list[i].id < __itt_group_splitter_max)
                res = (__itt_group_id)(res | group_list[i].id);
        return res;
    }
    else
    {
        for (i = 0; group_alias[i].env_var != NULL; i++)
            if (__itt_get_env_var(group_alias[i].env_var) != NULL)
                return group_alias[i].groups;
    }

    return res;
}