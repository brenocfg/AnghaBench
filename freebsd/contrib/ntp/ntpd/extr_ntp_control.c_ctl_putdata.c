#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* buf; unsigned int len; } ;
typedef  TYPE_1__ CtlMemBufT ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_putdata_ex (TYPE_1__*,int,int) ; 

__attribute__((used)) static void
ctl_putdata(
	const char *dp,
	unsigned int dlen,
	int bin			/* set to 1 when data is binary */
	)
{
	CtlMemBufT args[1];

	args[0].buf = dp;
	args[0].len = dlen;
	ctl_putdata_ex(args, 1, bin);
}