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
struct device {int /*<<< orphan*/  (* close ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSHK () ; 
 struct device* active_dev ; 
 int /*<<< orphan*/  k_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcibios_exit () ; 
 int /*<<< orphan*/ * rx_pool ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 

__attribute__((used)) static void close_driver (void)
{
  /* !!todo: loop over all 'handle_to_device[]' ? */
  struct device *dev = active_dev;

  if (dev && dev->close)
  {
    (*dev->close) (dev);
    FLUSHK();
  }

  active_dev = NULL;

#ifdef USE_32BIT_DRIVERS
  if (rx_pool)
  {
    k_free (rx_pool);
    rx_pool = NULL;
  }
  if (dev)
     pcibios_exit();
#endif
}