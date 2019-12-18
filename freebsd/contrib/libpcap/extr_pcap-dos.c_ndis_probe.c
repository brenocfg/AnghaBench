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
struct device {int /*<<< orphan*/ * release_rx_buf; int /*<<< orphan*/ * peek_rx_buf; int /*<<< orphan*/ * get_rx_buf; int /*<<< orphan*/ * copy_rx_buf; int /*<<< orphan*/  get_stats; int /*<<< orphan*/  close; int /*<<< orphan*/ * xmit; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int /*<<< orphan*/  NdisOpen () ; 
 int /*<<< orphan*/  ndis_close ; 
 int /*<<< orphan*/  ndis_open ; 
 int /*<<< orphan*/  ndis_stats ; 

__attribute__((used)) static int ndis_probe (struct device *dev)
{
#ifdef USE_NDIS2
  if (!NdisOpen())
     return (0);
#endif

  dev->open           = ndis_open;
  dev->xmit           = NULL;
  dev->close          = ndis_close;
  dev->get_stats      = ndis_stats;
  dev->copy_rx_buf    = NULL;       /* to-do */
  dev->get_rx_buf     = NULL;       /* upcall is from rmode driver */
  dev->peek_rx_buf    = NULL;
  dev->release_rx_buf = NULL;
  return (0);
}