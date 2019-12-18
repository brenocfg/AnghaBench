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
struct cc_drvdata {int /*<<< orphan*/  axim_mon_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXIM_MON_COMP_VALUE ; 
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_ioread (struct cc_drvdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 cc_axi_comp_count(struct cc_drvdata *drvdata)
{
	return FIELD_GET(AXIM_MON_COMP_VALUE,
			 cc_ioread(drvdata, drvdata->axim_mon_offset));
}