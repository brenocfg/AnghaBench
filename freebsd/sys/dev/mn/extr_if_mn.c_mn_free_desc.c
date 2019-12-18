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
struct trxd {struct trxd* vnext; } ;

/* Variables and functions */
 struct trxd* mn_desc_free ; 

__attribute__((used)) static void
mn_free_desc(struct trxd *dp)
{
	dp->vnext =  mn_desc_free;
	mn_desc_free = dp;
}