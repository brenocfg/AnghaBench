#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct snd_dbuf {scalar_t__ buf_addr; int /*<<< orphan*/  buf; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ ds_addr; scalar_t__ ds_len; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_verbose ; 

__attribute__((used)) static void
sndbuf_setmap(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct snd_dbuf *b = (struct snd_dbuf *)arg;

	if (snd_verbose > 3) {
		device_printf(b->dev, "sndbuf_setmap %lx, %lx; ",
		    (u_long)segs[0].ds_addr, (u_long)segs[0].ds_len);
		printf("%p -> %lx\n", b->buf, (u_long)segs[0].ds_addr);
	}
	if (error == 0)
		b->buf_addr = segs[0].ds_addr;
	else
		b->buf_addr = 0;
}