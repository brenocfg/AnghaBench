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
struct st_fdma_chan {TYPE_1__* fdev; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_slave_direction (int) ; 
 struct st_fdma_chan* to_st_fdma_chan (struct dma_chan*) ; 

__attribute__((used)) static inline struct st_fdma_chan *st_fdma_prep_common(struct dma_chan *chan,
		size_t len, enum dma_transfer_direction direction)
{
	struct st_fdma_chan *fchan;

	if (!chan || !len)
		return NULL;

	fchan = to_st_fdma_chan(chan);

	if (!is_slave_direction(direction)) {
		dev_err(fchan->fdev->dev, "bad direction?\n");
		return NULL;
	}

	return fchan;
}