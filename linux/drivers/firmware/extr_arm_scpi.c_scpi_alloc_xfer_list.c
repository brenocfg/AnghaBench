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
struct scpi_xfer {int /*<<< orphan*/  node; int /*<<< orphan*/  done; } ;
struct scpi_chan {int /*<<< orphan*/  xfers_list; struct scpi_xfer* xfers; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_SCPI_XFERS ; 
 struct scpi_xfer* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scpi_alloc_xfer_list(struct device *dev, struct scpi_chan *ch)
{
	int i;
	struct scpi_xfer *xfers;

	xfers = devm_kcalloc(dev, MAX_SCPI_XFERS, sizeof(*xfers), GFP_KERNEL);
	if (!xfers)
		return -ENOMEM;

	ch->xfers = xfers;
	for (i = 0; i < MAX_SCPI_XFERS; i++, xfers++) {
		init_completion(&xfers->done);
		list_add_tail(&xfers->node, &ch->xfers_list);
	}

	return 0;
}