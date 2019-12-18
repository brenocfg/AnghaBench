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
struct netif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPHYS ; 
 int /*<<< orphan*/  OF_call_method (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmabuf ; 
 int /*<<< orphan*/  netinstance ; 

__attribute__((used)) static void
ofwn_end(struct netif *nif)
{
#ifdef BROKEN
	/* dma-free freezes at least some Apple ethernet controllers */
	OF_call_method("dma-free", netinstance, 2, 0, dmabuf, MAXPHYS);
#endif
	OF_close(netinstance);
}