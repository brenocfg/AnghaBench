#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int is_io; int qosgrp; int get_rmt; int get_des_get_tail; int /*<<< orphan*/  did; void* mem_region; } ;
struct TYPE_11__ {int is_io; int index; int get_des; int get_wqp; int /*<<< orphan*/  did; void* mem_region; } ;
struct TYPE_9__ {int is_io; int coreid; int get_rev; int get_cur; int get_wqp; int /*<<< orphan*/  did; void* mem_region; } ;
struct TYPE_15__ {scalar_t__ u64; TYPE_5__ sindexload; TYPE_3__ smemload; TYPE_1__ sstatus; } ;
typedef  TYPE_7__ cvmx_pow_load_addr_t ;
struct TYPE_16__ {TYPE_6__** sindexload; TYPE_4__** smemload; TYPE_2__** sstatus; } ;
typedef  TYPE_8__ __cvmx_pow_dump_t ;
struct TYPE_14__ {int u64; } ;
struct TYPE_12__ {void* u64; } ;
struct TYPE_10__ {int u64; } ;

/* Variables and functions */
 void* CVMX_IO_SEG ; 
 int /*<<< orphan*/  CVMX_OCT_DID_TAG_TAG1 ; 
 int /*<<< orphan*/  CVMX_OCT_DID_TAG_TAG2 ; 
 int /*<<< orphan*/  CVMX_OCT_DID_TAG_TAG3 ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 
 int cvmx_octeon_num_cores () ; 
 int cvmx_pow_get_num_entries () ; 
 void* cvmx_read_csr (scalar_t__) ; 

__attribute__((used)) static int __cvmx_pow_capture_v1(void *buffer, int buffer_size)
{
    __cvmx_pow_dump_t *dump = (__cvmx_pow_dump_t*)buffer;
    int num_cores;
    int num_pow_entries = cvmx_pow_get_num_entries();
    int core;
    int index;
    int bits;

    if (buffer_size < (int)sizeof(__cvmx_pow_dump_t))
    {
        cvmx_dprintf("cvmx_pow_capture: Buffer too small\n");
        return -1;
    }

    num_cores = cvmx_octeon_num_cores();

    /* Read all core related state */
    for (core=0; core<num_cores; core++)
    {
        cvmx_pow_load_addr_t load_addr;
        load_addr.u64 = 0;
        load_addr.sstatus.mem_region = CVMX_IO_SEG;
        load_addr.sstatus.is_io = 1;
        load_addr.sstatus.did = CVMX_OCT_DID_TAG_TAG1;
        load_addr.sstatus.coreid = core;
        for (bits=0; bits<8; bits++)
        {
            load_addr.sstatus.get_rev = (bits & 1) != 0;
            load_addr.sstatus.get_cur = (bits & 2) != 0;
            load_addr.sstatus.get_wqp = (bits & 4) != 0;
            if ((load_addr.sstatus.get_cur == 0) && load_addr.sstatus.get_rev)
                dump->sstatus[core][bits].u64 = -1;
            else
                dump->sstatus[core][bits].u64 = cvmx_read_csr(load_addr.u64);
        }
    }

    /* Read all internal POW entries */
    for (index=0; index<num_pow_entries; index++)
    {
        cvmx_pow_load_addr_t load_addr;
        load_addr.u64 = 0;
        load_addr.smemload.mem_region = CVMX_IO_SEG;
        load_addr.smemload.is_io = 1;
        load_addr.smemload.did = CVMX_OCT_DID_TAG_TAG2;
        load_addr.smemload.index = index;
        for (bits=0; bits<3; bits++)
        {
            load_addr.smemload.get_des = (bits & 1) != 0;
            load_addr.smemload.get_wqp = (bits & 2) != 0;
            dump->smemload[index][bits].u64 = cvmx_read_csr(load_addr.u64);
        }
    }

    /* Read all group and queue pointers */
    for (index=0; index<16; index++)
    {
        cvmx_pow_load_addr_t load_addr;
        load_addr.u64 = 0;
        load_addr.sindexload.mem_region = CVMX_IO_SEG;
        load_addr.sindexload.is_io = 1;
        load_addr.sindexload.did = CVMX_OCT_DID_TAG_TAG3;
        load_addr.sindexload.qosgrp = index;
        for (bits=0; bits<4; bits++)
        {
            load_addr.sindexload.get_rmt =  (bits & 1) != 0;
            load_addr.sindexload.get_des_get_tail =  (bits & 2) != 0;
            /* The first pass only has 8 valid index values */
            if ((load_addr.sindexload.get_rmt == 0) &&
                (load_addr.sindexload.get_des_get_tail == 0) &&
                (index >= 8))
                dump->sindexload[index][bits].u64 = -1;
            else
                dump->sindexload[index][bits].u64 = cvmx_read_csr(load_addr.u64);
        }
    }
    return 0;
}