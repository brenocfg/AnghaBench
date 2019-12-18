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
typedef  int u_char ;
struct mss_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSS_IDATA ; 
 int MSS_IDXMASK ; 
 int /*<<< orphan*/  MSS_INDEX ; 
 int /*<<< orphan*/  ad_wait_init (struct mss_info*,int) ; 
 int io_rd (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_wr (struct mss_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ad_write(struct mss_info *mss, int reg, u_char data)
{
    	int x;

	/* printf("ad_write %d, %x\n", reg, data); */
    	ad_wait_init(mss, 1002000);
    	x = io_rd(mss, MSS_INDEX) & ~MSS_IDXMASK;
    	io_wr(mss, MSS_INDEX, (u_char)(reg & MSS_IDXMASK) | x);
    	io_wr(mss, MSS_IDATA, data);
}