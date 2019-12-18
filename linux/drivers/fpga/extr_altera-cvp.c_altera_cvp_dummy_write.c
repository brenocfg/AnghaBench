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
typedef  int u32 ;
struct altera_cvp_conf {int /*<<< orphan*/  (* write_data ) (struct altera_cvp_conf*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned int CVP_DUMMY_WR ; 
 int /*<<< orphan*/  VSE_CVP_MODE_CTRL ; 
 int VSE_CVP_MODE_CTRL_NUMCLKS_MASK ; 
 int VSE_CVP_MODE_CTRL_NUMCLKS_OFF ; 
 int /*<<< orphan*/  altera_read_config_dword (struct altera_cvp_conf*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  altera_write_config_dword (struct altera_cvp_conf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct altera_cvp_conf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void altera_cvp_dummy_write(struct altera_cvp_conf *conf)
{
	unsigned int i;
	u32 val;

	/* set 1 CVP clock cycle for every CVP Data Register Write */
	altera_read_config_dword(conf, VSE_CVP_MODE_CTRL, &val);
	val &= ~VSE_CVP_MODE_CTRL_NUMCLKS_MASK;
	val |= 1 << VSE_CVP_MODE_CTRL_NUMCLKS_OFF;
	altera_write_config_dword(conf, VSE_CVP_MODE_CTRL, val);

	for (i = 0; i < CVP_DUMMY_WR; i++)
		conf->write_data(conf, 0); /* dummy data, could be any value */
}