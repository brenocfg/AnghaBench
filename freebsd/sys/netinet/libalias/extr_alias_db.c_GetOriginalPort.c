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
typedef  int /*<<< orphan*/  u_short ;
struct alias_link {int /*<<< orphan*/  src_port; } ;

/* Variables and functions */

u_short
GetOriginalPort(struct alias_link *lnk)
{
	return (lnk->src_port);
}