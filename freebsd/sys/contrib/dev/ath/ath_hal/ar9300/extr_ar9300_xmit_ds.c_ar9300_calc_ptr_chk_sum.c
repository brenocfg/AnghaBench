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
typedef  int u_int16_t ;
typedef  int u_int ;
struct ar9300_txc {int ds_info; int ds_link; int ds_data0; int ds_ctl3; int ds_data1; int ds_ctl5; int ds_data2; int ds_ctl7; int ds_data3; int ds_ctl9; } ;

/* Variables and functions */
 int AR_tx_ptr_chk_sum ; 

__attribute__((used)) static inline u_int16_t
ar9300_calc_ptr_chk_sum(struct ar9300_txc *ads)
{
    u_int checksum;
    u_int16_t ptrchecksum;

    /* checksum = __bswap32(ads->ds_info) + ads->ds_link */
    checksum =    ads->ds_info + ads->ds_link
                + ads->ds_data0 + ads->ds_ctl3
                + ads->ds_data1 + ads->ds_ctl5
                + ads->ds_data2 + ads->ds_ctl7
                + ads->ds_data3 + ads->ds_ctl9;

    ptrchecksum = ((checksum & 0xffff) + (checksum >> 16)) & AR_tx_ptr_chk_sum;
    return ptrchecksum;
}