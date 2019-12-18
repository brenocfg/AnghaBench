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
struct drm_file {int /*<<< orphan*/  master; scalar_t__ magic; } ;
struct drm_device {int dummy; } ;
struct drm_auth {scalar_t__ magic; } ;
typedef  scalar_t__ drm_magic_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  drm_add_magic (int /*<<< orphan*/ ,struct drm_file*,scalar_t__) ; 
 scalar_t__ drm_find_file (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drm_magic_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int drm_getmagic(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	static drm_magic_t sequence = 0;
	struct drm_auth *auth = data;

	/* Find unique magic */
	if (file_priv->magic) {
		auth->magic = file_priv->magic;
	} else {
		do {
			mtx_lock(&drm_magic_lock);
			if (!sequence)
				++sequence;	/* reserve 0 */
			auth->magic = sequence++;
			mtx_unlock(&drm_magic_lock);
		} while (drm_find_file(file_priv->master, auth->magic));
		file_priv->magic = auth->magic;
		drm_add_magic(file_priv->master, file_priv, auth->magic);
	}

	DRM_DEBUG("%u\n", auth->magic);

	return 0;
}