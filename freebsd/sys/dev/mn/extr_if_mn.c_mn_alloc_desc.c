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
 int /*<<< orphan*/  M_MN ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct trxd* mn_desc_free ; 

__attribute__((used)) static struct trxd *
mn_alloc_desc(void)
{
	struct trxd *dp;

	dp = mn_desc_free;
	if (dp) 
		mn_desc_free = dp->vnext;
	else
		dp = (struct trxd *)malloc(sizeof *dp, M_MN, M_NOWAIT);
	return (dp);
}