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
struct pcmcia_device {TYPE_1__** resource; } ;
struct TYPE_2__ {int flags; int end; } ;

/* Variables and functions */
 int ENODEV ; 
 int IO_DATA_PATH_WIDTH ; 
 int IO_DATA_PATH_WIDTH_8 ; 
 int IO_DATA_PATH_WIDTH_AUTO ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 

__attribute__((used)) static int pcmcia_check_one_config(struct pcmcia_device *pdev, void *priv_data)
{
	int *is_kme = priv_data;

	if ((pdev->resource[0]->flags & IO_DATA_PATH_WIDTH)
	    != IO_DATA_PATH_WIDTH_8) {
		pdev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
		pdev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
	}
	pdev->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
	pdev->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;

	if (pdev->resource[1]->end) {
		pdev->resource[0]->end = 8;
		pdev->resource[1]->end = (*is_kme) ? 2 : 1;
	} else {
		if (pdev->resource[0]->end < 16)
			return -ENODEV;
	}

	return pcmcia_request_io(pdev);
}