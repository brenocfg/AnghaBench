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
typedef  int uint32_t ;
struct dtsec_regs {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fman_dtsec_set_bucket (struct dtsec_regs*,scalar_t__,int /*<<< orphan*/ ) ; 

void fman_dtsec_set_hash_table(struct dtsec_regs *regs, uint32_t crc, bool mcast, bool ghtx)
{
    int32_t bucket;
    if (ghtx)
        bucket = (int32_t)((crc >> 23) & 0x1ff);
    else {
        bucket = (int32_t)((crc >> 24) & 0xff);
        /* if !ghtx and mcast the bit must be set in gaddr instead of igaddr. */
        if (mcast)
            bucket += 0x100;
    }
    fman_dtsec_set_bucket(regs, bucket, TRUE);
}