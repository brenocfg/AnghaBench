#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
typedef  size_t __cvmx_pow_list_types_t ;
struct TYPE_9__ {TYPE_3__** smemload; } ;
typedef  TYPE_4__ __cvmx_pow_dump_t ;
struct TYPE_7__ {size_t next_index; } ;
struct TYPE_6__ {size_t next_index; size_t fwd_index; } ;
struct TYPE_8__ {TYPE_2__ s_smemload0; TYPE_1__ s_smemload3_cn68xx; } ;

/* Variables and functions */
 size_t CVMX_POW_LIST_CORE ; 
 size_t CVMX_POW_LIST_INPUT ; 
 int /*<<< orphan*/  OCTEON_FEATURE_PKND ; 
 int /*<<< orphan*/  __cvmx_pow_display_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,size_t,size_t) ; 
 scalar_t__ __cvmx_pow_entry_mark_list (size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * __cvmx_pow_list_names ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cvmx_pow_display_list_and_walk(__cvmx_pow_list_types_t entry_type,
                                             __cvmx_pow_dump_t *dump, uint8_t entry_list[],
                                             int valid, int has_one, uint64_t head, uint64_t tail)
{
    __cvmx_pow_display_list(__cvmx_pow_list_names[entry_type], 0, valid, has_one, head, tail);
    if (valid)
    {
        if (has_one)
            __cvmx_pow_entry_mark_list(head, entry_type, entry_list);
        else
        {
            while (head != tail)
            {
                if (__cvmx_pow_entry_mark_list(head, entry_type, entry_list))
                    break;
                if (octeon_has_feature(OCTEON_FEATURE_PKND))
                {
                    if (entry_type >= CVMX_POW_LIST_INPUT && entry_type < CVMX_POW_LIST_CORE)
                 
                        head = dump->smemload[head][4].s_smemload3_cn68xx.next_index;
                    else
                        head = dump->smemload[head][4].s_smemload3_cn68xx.fwd_index;
                }
                else
                    head = dump->smemload[head][0].s_smemload0.next_index;
            }
            __cvmx_pow_entry_mark_list(tail, entry_type, entry_list);
        }
    }
}