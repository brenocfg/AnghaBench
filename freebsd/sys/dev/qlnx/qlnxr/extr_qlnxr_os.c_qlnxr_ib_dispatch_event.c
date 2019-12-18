#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  port_num; } ;
struct ib_event {int event; TYPE_1__ element; int /*<<< orphan*/ * device; } ;
struct TYPE_5__ {int /*<<< orphan*/  ha; int /*<<< orphan*/  ibdev; } ;
typedef  TYPE_2__ qlnxr_dev_t ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 

__attribute__((used)) static void
qlnxr_ib_dispatch_event(qlnxr_dev_t *dev, uint8_t port_num,
	enum ib_event_type type)
{
        struct ib_event ibev;

	QL_DPRINT12(dev->ha, "enter\n");

        ibev.device = &dev->ibdev;
        ibev.element.port_num = port_num;
        ibev.event = type;

        ib_dispatch_event(&ibev);

	QL_DPRINT12(dev->ha, "exit\n");
}