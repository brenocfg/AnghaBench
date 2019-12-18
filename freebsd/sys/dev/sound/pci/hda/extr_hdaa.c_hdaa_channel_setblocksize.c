#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct hdaa_chan {int /*<<< orphan*/  blksz; TYPE_1__* pdevinfo; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_2__ {int /*<<< orphan*/  chan_blkcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdaa_channel_setfragments (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
hdaa_channel_setblocksize(kobj_t obj, void *data, uint32_t blksz)
{
	struct hdaa_chan *ch = data;

	hdaa_channel_setfragments(obj, data, blksz, ch->pdevinfo->chan_blkcnt);

	return (ch->blksz);
}