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
struct aoa_dma {int /*<<< orphan*/  channel; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  aoa_dma_delete (struct aoa_dma*) ; 
 int /*<<< orphan*/  dbdma_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aoa_chan_free(kobj_t obj, void *data)
{
	struct aoa_dma 	*dma = data;

	sndbuf_free(dma->buf);
	dbdma_free_channel(dma->channel);
	aoa_dma_delete(dma);

	return (0);
}