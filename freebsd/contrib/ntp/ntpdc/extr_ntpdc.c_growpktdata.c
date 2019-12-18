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
 scalar_t__ INCDATASIZE ; 
 int /*<<< orphan*/  erealloc_zero (int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  pktdata ; 
 scalar_t__ pktdatasize ; 

__attribute__((used)) static void
growpktdata(void)
{
	size_t priorsz;

	priorsz = (size_t)pktdatasize;
	pktdatasize += INCDATASIZE;
	pktdata = erealloc_zero(pktdata, (size_t)pktdatasize, priorsz);
}