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
struct device {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSUSED (int) ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  NdisInit (int) ; 

__attribute__((used)) static int ndis_open (struct device *dev)
{
  int promis = (dev->flags & IFF_PROMISC);

#ifdef USE_NDIS2
  if (!NdisInit(promis))
     return (0);
  return (1);
#else
  ARGSUSED (promis);
  return (0);
#endif
}