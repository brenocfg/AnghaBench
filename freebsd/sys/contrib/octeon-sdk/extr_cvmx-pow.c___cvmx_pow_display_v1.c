#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  entry_list ;
struct TYPE_24__ {TYPE_15__** smemload; TYPE_11__** sindexload; TYPE_6__** sstatus; } ;
typedef  TYPE_16__ __cvmx_pow_dump_t ;
struct TYPE_33__ {int /*<<< orphan*/  rmt_head; int /*<<< orphan*/  rmt_one; int /*<<< orphan*/  rmt_val; scalar_t__ rmt_is_head; } ;
struct TYPE_32__ {int /*<<< orphan*/  loc_tail; int /*<<< orphan*/  loc_head; int /*<<< orphan*/  loc_one; int /*<<< orphan*/  loc_val; int /*<<< orphan*/  free_tail; int /*<<< orphan*/  free_head; int /*<<< orphan*/  free_one; int /*<<< orphan*/  free_val; } ;
struct TYPE_31__ {int /*<<< orphan*/  des_tail; int /*<<< orphan*/  des_head; int /*<<< orphan*/  des_one; int /*<<< orphan*/  des_val; int /*<<< orphan*/  nosched_tail; int /*<<< orphan*/  nosched_head; int /*<<< orphan*/  nosched_one; int /*<<< orphan*/  nosched_val; } ;
struct TYPE_29__ {int /*<<< orphan*/  pend_wqp; } ;
struct TYPE_28__ {int pend_switch; int pend_switch_full; int pend_switch_null; int pend_desched; int pend_desched_switch; int pend_nosched; int pend_grp; int pend_null_rd; int pend_nosched_clr; int pend_index; scalar_t__ pend_type; int pend_tag; scalar_t__ pend_new_work_wait; scalar_t__ pend_new_work; } ;
struct TYPE_27__ {scalar_t__ tag_type; int tag; int index; int grp; int link_index; scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_26__ {int revlink_index; } ;
struct TYPE_25__ {int /*<<< orphan*/  wqp; } ;
struct TYPE_30__ {TYPE_5__ s_sstatus1; TYPE_4__ s_sstatus0; TYPE_3__ s_sstatus2; TYPE_2__ s_sstatus3; TYPE_1__ s_sstatus4; } ;
struct TYPE_22__ {int nosched; scalar_t__ pend_type; int pend_tag; scalar_t__ pend_switch; } ;
struct TYPE_21__ {scalar_t__ tag_type; int tag; int grp; int next_index; scalar_t__ tail; } ;
struct TYPE_20__ {int /*<<< orphan*/  wqp; } ;
struct TYPE_23__ {TYPE_14__ s_smemload2; TYPE_13__ s_smemload0; TYPE_12__ s_smemload1; } ;
struct TYPE_18__ {int /*<<< orphan*/  rmt_tail; } ;
struct TYPE_19__ {TYPE_10__ sindexload3; TYPE_9__ sindexload2; TYPE_8__ sindexload0; TYPE_7__ sindexload1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST64 (int /*<<< orphan*/ ) ; 
 scalar_t__ CVMX_POW_LIST_CORE ; 
 int CVMX_POW_LIST_DESCHED ; 
 int CVMX_POW_LIST_FREE ; 
 int CVMX_POW_LIST_INPUT ; 
 int CVMX_POW_LIST_NOSCHED ; 
 scalar_t__ CVMX_POW_TAG_TYPE_NULL_NULL ; 
 char* OCT_TAG_TYPE_STRING (scalar_t__) ; 
 int /*<<< orphan*/  __cvmx_pow_display_list (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_pow_display_list_and_walk (int,TYPE_16__*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_pow_entry_mark_list (int,scalar_t__,size_t*) ; 
 char** __cvmx_pow_list_names ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 
 int cvmx_octeon_num_cores () ; 
 int cvmx_pow_get_num_entries () ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void __cvmx_pow_display_v1(void *buffer, int buffer_size)
{
    __cvmx_pow_dump_t *dump = (__cvmx_pow_dump_t*)buffer;
    int num_pow_entries = cvmx_pow_get_num_entries();
    int num_cores;
    int core;
    int index;
    uint8_t entry_list[2048];

    if (buffer_size < (int)sizeof(__cvmx_pow_dump_t))
    {
        cvmx_dprintf("cvmx_pow_dump: Buffer too small\n");
        return;
    }

    memset(entry_list, 0, sizeof(entry_list));
    num_cores = cvmx_octeon_num_cores();

    /* Print the free list info */
    __cvmx_pow_display_list_and_walk(CVMX_POW_LIST_FREE, dump, entry_list,
                                     dump->sindexload[0][0].sindexload0.free_val,
                                     dump->sindexload[0][0].sindexload0.free_one,
                                     dump->sindexload[0][0].sindexload0.free_head,
                                     dump->sindexload[0][0].sindexload0.free_tail);

    /* Print the core state */
    for (core=0; core<num_cores; core++)
    {
        const int bit_rev = 1;
        const int bit_cur = 2;
        const int bit_wqp = 4;
        printf("Core %d State:  tag=%s,0x%08x", core,
               OCT_TAG_TYPE_STRING(dump->sstatus[core][bit_cur].s_sstatus2.tag_type),
               dump->sstatus[core][bit_cur].s_sstatus2.tag);
        if (dump->sstatus[core][bit_cur].s_sstatus2.tag_type != CVMX_POW_TAG_TYPE_NULL_NULL)
        {
            __cvmx_pow_entry_mark_list(dump->sstatus[core][bit_cur].s_sstatus2.index, CVMX_POW_LIST_CORE + core, entry_list);
            printf(" grp=%d",                   dump->sstatus[core][bit_cur].s_sstatus2.grp);
            printf(" wqp=0x%016llx",            CAST64(dump->sstatus[core][bit_cur|bit_wqp].s_sstatus4.wqp));
            printf(" index=%d",                 dump->sstatus[core][bit_cur].s_sstatus2.index);
            if (dump->sstatus[core][bit_cur].s_sstatus2.head)
                printf(" head");
            else
                printf(" prev=%d", dump->sstatus[core][bit_cur|bit_rev].s_sstatus3.revlink_index);
            if (dump->sstatus[core][bit_cur].s_sstatus2.tail)
                printf(" tail");
            else
                printf(" next=%d", dump->sstatus[core][bit_cur].s_sstatus2.link_index);
        }

        if (dump->sstatus[core][0].s_sstatus0.pend_switch)
        {
            printf(" pend_switch=%d",           dump->sstatus[core][0].s_sstatus0.pend_switch);
            printf(" pend_switch_full=%d",      dump->sstatus[core][0].s_sstatus0.pend_switch_full);
            printf(" pend_switch_null=%d",      dump->sstatus[core][0].s_sstatus0.pend_switch_null);
        }

        if (dump->sstatus[core][0].s_sstatus0.pend_desched)
        {
            printf(" pend_desched=%d",          dump->sstatus[core][0].s_sstatus0.pend_desched);
            printf(" pend_desched_switch=%d",   dump->sstatus[core][0].s_sstatus0.pend_desched_switch);
            printf(" pend_nosched=%d",          dump->sstatus[core][0].s_sstatus0.pend_nosched);
            if (dump->sstatus[core][0].s_sstatus0.pend_desched_switch)
                printf(" pend_grp=%d",              dump->sstatus[core][0].s_sstatus0.pend_grp);
        }

        if (dump->sstatus[core][0].s_sstatus0.pend_new_work)
        {
            if (dump->sstatus[core][0].s_sstatus0.pend_new_work_wait)
                printf(" (Waiting for work)");
            else
                printf(" (Getting work)");
        }
        if (dump->sstatus[core][0].s_sstatus0.pend_null_rd)
            printf(" pend_null_rd=%d",          dump->sstatus[core][0].s_sstatus0.pend_null_rd);
        if (dump->sstatus[core][0].s_sstatus0.pend_nosched_clr)
        {
            printf(" pend_nosched_clr=%d",      dump->sstatus[core][0].s_sstatus0.pend_nosched_clr);
            printf(" pend_index=%d",            dump->sstatus[core][0].s_sstatus0.pend_index);
        }
        if (dump->sstatus[core][0].s_sstatus0.pend_switch ||
            (dump->sstatus[core][0].s_sstatus0.pend_desched &&
            dump->sstatus[core][0].s_sstatus0.pend_desched_switch))
        {
            printf(" pending tag=%s,0x%08x",
                   OCT_TAG_TYPE_STRING(dump->sstatus[core][0].s_sstatus0.pend_type),
                   dump->sstatus[core][0].s_sstatus0.pend_tag);
        }
        if (dump->sstatus[core][0].s_sstatus0.pend_nosched_clr)
            printf(" pend_wqp=0x%016llx\n",     CAST64(dump->sstatus[core][bit_wqp].s_sstatus1.pend_wqp));
        printf("\n");
    }

    /* Print out the state of the nosched list and the 16 deschedule lists. */
    __cvmx_pow_display_list_and_walk(CVMX_POW_LIST_NOSCHED, dump, entry_list,
                            dump->sindexload[0][2].sindexload1.nosched_val,
                            dump->sindexload[0][2].sindexload1.nosched_one,
                            dump->sindexload[0][2].sindexload1.nosched_head,
                            dump->sindexload[0][2].sindexload1.nosched_tail);
    for (index=0; index<16; index++)
    {
        __cvmx_pow_display_list_and_walk(CVMX_POW_LIST_DESCHED + index, dump, entry_list,
                                dump->sindexload[index][2].sindexload1.des_val,
                                dump->sindexload[index][2].sindexload1.des_one,
                                dump->sindexload[index][2].sindexload1.des_head,
                                dump->sindexload[index][2].sindexload1.des_tail);
    }

    /* Print out the state of the 8 internal input queues */
    for (index=0; index<8; index++)
    {
        __cvmx_pow_display_list_and_walk(CVMX_POW_LIST_INPUT + index, dump, entry_list,
                                dump->sindexload[index][0].sindexload0.loc_val,
                                dump->sindexload[index][0].sindexload0.loc_one,
                                dump->sindexload[index][0].sindexload0.loc_head,
                                dump->sindexload[index][0].sindexload0.loc_tail);
    }

    /* Print out the state of the 16 memory queues */
    for (index=0; index<8; index++)
    {
        const char *name;
        if (dump->sindexload[index][1].sindexload2.rmt_is_head)
            name = "Queue %da Memory (is head)";
        else
            name = "Queue %da Memory";
        __cvmx_pow_display_list(name, index,
                                dump->sindexload[index][1].sindexload2.rmt_val,
                                dump->sindexload[index][1].sindexload2.rmt_one,
                                dump->sindexload[index][1].sindexload2.rmt_head,
                                dump->sindexload[index][3].sindexload3.rmt_tail);
        if (dump->sindexload[index+8][1].sindexload2.rmt_is_head)
            name = "Queue %db Memory (is head)";
        else
            name = "Queue %db Memory";
        __cvmx_pow_display_list(name, index,
                                dump->sindexload[index+8][1].sindexload2.rmt_val,
                                dump->sindexload[index+8][1].sindexload2.rmt_one,
                                dump->sindexload[index+8][1].sindexload2.rmt_head,
                                dump->sindexload[index+8][3].sindexload3.rmt_tail);
    }

    /* Print out each of the internal POW entries. Each entry has a tag, group,
        wqe, and possibly a next pointer. The next pointer is only valid if this
        entry isn't make as a tail */
    for (index=0; index<num_pow_entries; index++)
    {
        printf("Entry %d(%-10s): tag=%s,0x%08x grp=%d wqp=0x%016llx", index,
               __cvmx_pow_list_names[entry_list[index]],
               OCT_TAG_TYPE_STRING(dump->smemload[index][0].s_smemload0.tag_type),
               dump->smemload[index][0].s_smemload0.tag,
               dump->smemload[index][0].s_smemload0.grp,
               CAST64(dump->smemload[index][2].s_smemload1.wqp));
        if (dump->smemload[index][0].s_smemload0.tail)
            printf(" tail");
        else
            printf(" next=%d", dump->smemload[index][0].s_smemload0.next_index);
        if (entry_list[index] >= CVMX_POW_LIST_DESCHED)
        {
            printf(" nosched=%d", dump->smemload[index][1].s_smemload2.nosched);
            if (dump->smemload[index][1].s_smemload2.pend_switch)
            {
                printf(" pending tag=%s,0x%08x",
                       OCT_TAG_TYPE_STRING(dump->smemload[index][1].s_smemload2.pend_type),
                       dump->smemload[index][1].s_smemload2.pend_tag);
            }
        }
        printf("\n");
    }
}