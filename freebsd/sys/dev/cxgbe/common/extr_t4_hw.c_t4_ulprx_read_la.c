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
typedef  void* u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ULP_RX_LA_CTL ; 
 int /*<<< orphan*/  A_ULP_RX_LA_RDDATA ; 
 int /*<<< orphan*/  A_ULP_RX_LA_RDPTR ; 
 int /*<<< orphan*/  A_ULP_RX_LA_WRPTR ; 
 unsigned int ULPRX_LA_SIZE ; 
 void* t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 

void t4_ulprx_read_la(struct adapter *adap, u32 *la_buf)
{
	unsigned int i, j;

	for (i = 0; i < 8; i++) {
		u32 *p = la_buf + i;

		t4_write_reg(adap, A_ULP_RX_LA_CTL, i);
		j = t4_read_reg(adap, A_ULP_RX_LA_WRPTR);
		t4_write_reg(adap, A_ULP_RX_LA_RDPTR, j);
		for (j = 0; j < ULPRX_LA_SIZE; j++, p += 8)
			*p = t4_read_reg(adap, A_ULP_RX_LA_RDDATA);
	}
}