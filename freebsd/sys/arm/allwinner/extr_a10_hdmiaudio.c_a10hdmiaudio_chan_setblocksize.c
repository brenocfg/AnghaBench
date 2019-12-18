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
typedef  int uint32_t ;
struct a10hdmiaudio_chinfo {int blocksize; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
a10hdmiaudio_chan_setblocksize(kobj_t obj, void *data, uint32_t blocksize)
{
	struct a10hdmiaudio_chinfo *ch = data;

	ch->blocksize = blocksize & ~3;

	return (ch->blocksize);
}