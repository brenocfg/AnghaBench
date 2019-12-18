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
struct xdma_channel {scalar_t__ chan; } ;
struct softdma_desc {int dummy; } ;
struct softdma_channel {int descs_num; int /*<<< orphan*/  descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
softdma_desc_alloc(struct xdma_channel *xchan)
{
	struct softdma_channel *chan;
	uint32_t nsegments;

	chan = (struct softdma_channel *)xchan->chan;

	nsegments = chan->descs_num;

	chan->descs = malloc(nsegments * sizeof(struct softdma_desc),
	    M_DEVBUF, (M_WAITOK | M_ZERO));

	return (0);
}