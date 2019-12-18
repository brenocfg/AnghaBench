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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MA_INT_WRAP_STATUS ; 
 int /*<<< orphan*/  CH_ALERT (struct adapter*,char*,int /*<<< orphan*/ ,int) ; 
 int G_MEM_WRAP_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_MEM_WRAP_CLIENT_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ma_wrap_status(struct adapter *adap, int arg, bool verbose)
{
	u32 v;

	v = t4_read_reg(adap, A_MA_INT_WRAP_STATUS);
	CH_ALERT(adap,
	    "MA address wrap-around error by client %u to address %#x\n",
	    G_MEM_WRAP_CLIENT_NUM(v), G_MEM_WRAP_ADDRESS(v) << 4);
	t4_write_reg(adap, A_MA_INT_WRAP_STATUS, v);

	return (false);
}