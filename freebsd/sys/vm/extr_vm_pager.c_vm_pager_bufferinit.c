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
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSWBUF_MIN ; 
 int /*<<< orphan*/  UMA_ALIGN_CACHE ; 
 int UMA_ZONE_NOFREE ; 
 int UMA_ZONE_VM ; 
 int /*<<< orphan*/  nswbuf_max ; 
 int /*<<< orphan*/  pbuf_ctor ; 
 int /*<<< orphan*/  pbuf_dtor ; 
 int /*<<< orphan*/  pbuf_init ; 
 int /*<<< orphan*/  pbuf_zone ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uma_zone_set_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_pager_bufferinit(void)
{

	/* Main zone for paging bufs. */
	pbuf_zone = uma_zcreate("pbuf", sizeof(struct buf),
	    pbuf_ctor, pbuf_dtor, pbuf_init, NULL, UMA_ALIGN_CACHE,
	    UMA_ZONE_VM | UMA_ZONE_NOFREE);
	/* Few systems may still use this zone directly, so it needs a limit. */
	nswbuf_max += uma_zone_set_max(pbuf_zone, NSWBUF_MIN);
}