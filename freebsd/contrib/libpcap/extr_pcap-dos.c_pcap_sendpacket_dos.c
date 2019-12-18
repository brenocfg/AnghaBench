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
struct device {int (* xmit ) (struct device*,void const*,size_t) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 struct device* get_device (int /*<<< orphan*/ ) ; 
 int stub1 (struct device*,void const*,size_t) ; 

__attribute__((used)) static int pcap_sendpacket_dos (pcap_t *p, const void *buf, size_t len)
{
  struct device *dev = p ? get_device(p->fd) : NULL;

  if (!dev || !dev->xmit)
     return (-1);
  return (*dev->xmit) (dev, buf, len);
}