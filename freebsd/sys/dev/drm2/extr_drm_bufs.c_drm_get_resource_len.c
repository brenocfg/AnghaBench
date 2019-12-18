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
struct drm_device {int /*<<< orphan*/  pcir_lock; int /*<<< orphan*/ * pcir; } ;

/* Variables and functions */
 scalar_t__ drm_alloc_resource (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 unsigned long rman_get_size (int /*<<< orphan*/ ) ; 

unsigned long drm_get_resource_len(struct drm_device *dev,
				   unsigned int resource)
{
	unsigned long len;

	mtx_lock(&dev->pcir_lock);

	if (drm_alloc_resource(dev, resource) != 0)
		return 0;

	len = rman_get_size(dev->pcir[resource]);

	mtx_unlock(&dev->pcir_lock);

	return (len);
}