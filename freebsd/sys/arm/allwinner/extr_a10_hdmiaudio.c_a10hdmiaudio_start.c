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
struct a10hdmiaudio_chinfo {scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  a10hdmiaudio_dmaconfig (struct a10hdmiaudio_chinfo*) ; 
 int /*<<< orphan*/  a10hdmiaudio_transfer (struct a10hdmiaudio_chinfo*) ; 

__attribute__((used)) static void
a10hdmiaudio_start(struct a10hdmiaudio_chinfo *ch)
{
	ch->pos = 0;

	/* Configure DMA channel */
	a10hdmiaudio_dmaconfig(ch);

	/* Start DMA transfer */
	a10hdmiaudio_transfer(ch);
}