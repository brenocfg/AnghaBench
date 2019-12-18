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
struct resource_i {int dummy; } ;
struct resource {struct resource* __r_i; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  XXX ; 
 int bus_alloc_resource_any_cb (struct resource*,int /*<<< orphan*/ ,int,int*,unsigned int) ; 
 int /*<<< orphan*/  free (struct resource*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct resource*,int /*<<< orphan*/ ,int,int*,unsigned int) ; 

struct resource *
bus_alloc_resource_any(device_t dev, int type, int *rid, unsigned int flags)
{
	struct resource *res;
	int ret = EINVAL;

	res = malloc(sizeof(*res), XXX, XXX);
	if (res == NULL)
		return (NULL);

	res->__r_i = malloc(sizeof(struct resource_i), XXX, XXX);
	if (res->__r_i == NULL) {
		free(res, XXX);
		return (NULL);
	}

	if (bus_alloc_resource_any_cb != NULL)
		ret = (*bus_alloc_resource_any_cb)(res, dev, type, rid, flags);
	if (ret == 0)
		return (res);

	free(res->__r_i, XXX);
	free(res, XXX);
	return (NULL);
}