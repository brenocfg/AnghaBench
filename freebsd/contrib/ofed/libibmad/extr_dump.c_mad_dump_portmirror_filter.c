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

/* Variables and functions */
 int /*<<< orphan*/  IB_PMF_FIRST_F ; 
 int /*<<< orphan*/  IB_PMF_LAST_F ; 
 int /*<<< orphan*/  _dump_fields (char*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mad_dump_portmirror_filter(char *buf, int bufsz, void *val, int valsz)
{
	_dump_fields(buf, bufsz, val, IB_PMF_FIRST_F, IB_PMF_LAST_F);
}