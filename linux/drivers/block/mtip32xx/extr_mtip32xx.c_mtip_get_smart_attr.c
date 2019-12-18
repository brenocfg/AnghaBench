#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smart_attr {unsigned int attr_id; } ;
struct mtip_port {int* identify; TYPE_2__* dd; scalar_t__ smart_buf; int /*<<< orphan*/  smart_buf_dma; int /*<<< orphan*/  identify_valid; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_SECT_SIZE ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (struct smart_attr*,struct smart_attr*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtip_get_smart_data (struct mtip_port*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtip_get_smart_attr(struct mtip_port *port, unsigned int id,
						struct smart_attr *attrib)
{
	int rv, i;
	struct smart_attr *pattr;

	if (!attrib)
		return -EINVAL;

	if (!port->identify_valid) {
		dev_warn(&port->dd->pdev->dev, "IDENTIFY DATA not valid\n");
		return -EPERM;
	}
	if (!(port->identify[82] & 0x1)) {
		dev_warn(&port->dd->pdev->dev, "SMART not supported\n");
		return -EPERM;
	}
	if (!(port->identify[85] & 0x1)) {
		dev_warn(&port->dd->pdev->dev, "SMART not enabled\n");
		return -EPERM;
	}

	memset(port->smart_buf, 0, ATA_SECT_SIZE);
	rv = mtip_get_smart_data(port, port->smart_buf, port->smart_buf_dma);
	if (rv) {
		dev_warn(&port->dd->pdev->dev, "Failed to ge SMART data\n");
		return rv;
	}

	pattr = (struct smart_attr *)(port->smart_buf + 2);
	for (i = 0; i < 29; i++, pattr++)
		if (pattr->attr_id == id) {
			memcpy(attrib, pattr, sizeof(struct smart_attr));
			break;
		}

	if (i == 29) {
		dev_warn(&port->dd->pdev->dev,
			"Query for invalid SMART attribute ID\n");
		rv = -EINVAL;
	}

	return rv;
}