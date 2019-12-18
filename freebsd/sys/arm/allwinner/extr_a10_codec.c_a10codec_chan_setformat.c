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
typedef  int /*<<< orphan*/  uint32_t ;
struct a10codec_chinfo {int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */

__attribute__((used)) static int
a10codec_chan_setformat(kobj_t obj, void *data, uint32_t format)
{
	struct a10codec_chinfo *ch = data;

	ch->format = format;

	return (0);
}