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
struct coresight_device {int /*<<< orphan*/  dev_type; int /*<<< orphan*/  pdata; int /*<<< orphan*/  node; int /*<<< orphan*/  dev; } ;
struct coresight_desc {int /*<<< orphan*/  dev_type; int /*<<< orphan*/  pdata; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CORESIGHT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct coresight_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_devs ; 
 int /*<<< orphan*/  cs_mtx ; 
 int /*<<< orphan*/  link ; 
 struct coresight_device* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

int
coresight_register(struct coresight_desc *desc)
{
	struct coresight_device *cs_dev;

	cs_dev = malloc(sizeof(struct coresight_device),
	    M_CORESIGHT, M_WAITOK | M_ZERO);
	cs_dev->dev = desc->dev;
	cs_dev->node = ofw_bus_get_node(desc->dev);
	cs_dev->pdata = desc->pdata;
	cs_dev->dev_type = desc->dev_type;

	mtx_lock(&cs_mtx);
	TAILQ_INSERT_TAIL(&cs_devs, cs_dev, link);
	mtx_unlock(&cs_mtx);

	return (0);
}