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
typedef  unsigned long long uint64_t ;
typedef  unsigned long long cvmx_tra_filt_t ;
struct TYPE_3__ {scalar_t__ reserved_6_7; scalar_t__ reserved_10_14; scalar_t__ reserved_27_27; scalar_t__ reserved_56_57; scalar_t__ reserved_60_61; } ;
struct TYPE_4__ {unsigned long long u64; TYPE_1__ cn63xx; } ;
typedef  TYPE_2__ cvmx_tra_filt_cmd_t ;

/* Variables and functions */
 unsigned long long CVMX_TRA_FILT_ALL ; 
 unsigned long long CVMX_TRA_FILT_DWB ; 
 unsigned long long CVMX_TRA_FILT_IOBDMA ; 
 unsigned long long CVMX_TRA_FILT_IOBLD16 ; 
 unsigned long long CVMX_TRA_FILT_IOBLD32 ; 
 unsigned long long CVMX_TRA_FILT_IOBLD64 ; 
 unsigned long long CVMX_TRA_FILT_IOBLD8 ; 
 unsigned long long CVMX_TRA_FILT_IOBST ; 
 unsigned long long CVMX_TRA_FILT_LDD ; 
 unsigned long long CVMX_TRA_FILT_LDI ; 
 unsigned long long CVMX_TRA_FILT_LDT ; 
 unsigned long long CVMX_TRA_FILT_PL2 ; 
 unsigned long long CVMX_TRA_FILT_PSL1 ; 
 unsigned long long CVMX_TRA_FILT_SAA ; 
 unsigned long long CVMX_TRA_FILT_STC ; 
 unsigned long long CVMX_TRA_FILT_STF ; 
 unsigned long long CVMX_TRA_FILT_STP ; 
 unsigned long long CVMX_TRA_FILT_STT ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_CN5XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t __cvmx_tra_set_filter_cmd_mask(cvmx_tra_filt_t filter)
{
    cvmx_tra_filt_cmd_t filter_command;

    if (OCTEON_IS_MODEL(OCTEON_CN3XXX) || OCTEON_IS_MODEL(OCTEON_CN5XXX))
    {
        /* Bit positions of filter commands are different, map it accordingly */
        uint64_t cmd = 0;
        if ((filter & CVMX_TRA_FILT_ALL) == -1ull)
        {
            if (OCTEON_IS_MODEL(OCTEON_CN5XXX))
                cmd = 0x1ffff;
            else
                cmd = 0xffff;
        }
        if (filter & CVMX_TRA_FILT_DWB)
            cmd |= 1ull<<0;
        if (filter & CVMX_TRA_FILT_PL2)
            cmd |= 1ull<<1;
        if (filter & CVMX_TRA_FILT_PSL1)
            cmd |= 1ull<<2;
        if (filter & CVMX_TRA_FILT_LDD)
            cmd |= 1ull<<3;
        if (filter & CVMX_TRA_FILT_LDI)
            cmd |= 1ull<<4;
        if (filter & CVMX_TRA_FILT_LDT)
            cmd |= 1ull<<5;
        if (filter & CVMX_TRA_FILT_STF)
            cmd |= 1ull<<6;
        if (filter & CVMX_TRA_FILT_STC)
            cmd |= 1ull<<7;
        if (filter & CVMX_TRA_FILT_STP)
            cmd |= 1ull<<8;
        if (filter & CVMX_TRA_FILT_STT)
            cmd |= 1ull<<9;
        if (filter & CVMX_TRA_FILT_IOBLD8)
            cmd |= 1ull<<10;
        if (filter & CVMX_TRA_FILT_IOBLD16)
            cmd |= 1ull<<11;
        if (filter & CVMX_TRA_FILT_IOBLD32)
            cmd |= 1ull<<12;
        if (filter & CVMX_TRA_FILT_IOBLD64)
            cmd |= 1ull<<13;
        if (filter & CVMX_TRA_FILT_IOBST)
            cmd |= 1ull<<14;
        if (filter & CVMX_TRA_FILT_IOBDMA)
            cmd |= 1ull<<15;
        if (OCTEON_IS_MODEL(OCTEON_CN5XXX) && (filter & CVMX_TRA_FILT_SAA))
            cmd |= 1ull<<16;

        filter_command.u64 = cmd;
    }
    else
    {
        if ((filter & CVMX_TRA_FILT_ALL) == -1ull)
            filter_command.u64 = CVMX_TRA_FILT_ALL;
        else
            filter_command.u64 = filter;

        filter_command.cn63xx.reserved_60_61 = 0;
        filter_command.cn63xx.reserved_56_57 = 0;
        filter_command.cn63xx.reserved_27_27 = 0;
        filter_command.cn63xx.reserved_10_14 = 0;
        filter_command.cn63xx.reserved_6_7 = 0;
    }
    return filter_command.u64;
}