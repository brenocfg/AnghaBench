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
struct gmesh {int dummy; } ;
typedef  int /*<<< orphan*/ * const_efidp ;

/* Variables and functions */
 scalar_t__ DevicePathSubType (int /*<<< orphan*/ *) ; 
 scalar_t__ DevicePathType (int /*<<< orphan*/ *) ; 
 int EDOOFUS ; 
 int EINVAL ; 
 scalar_t__ END_DEVICE_PATH_TYPE ; 
 int ENOMEM ; 
 uintptr_t MAX_DP_SANITY ; 
 scalar_t__ MEDIA_DEVICE_PATH ; 
 scalar_t__ MEDIA_HARDDRIVE_DP ; 
 scalar_t__ NextDevicePathNode (int /*<<< orphan*/ *) ; 
 int efi_cdrom_to_unix (struct gmesh*,int /*<<< orphan*/ *,char**,char**,char**) ; 
 int efi_floppy_to_unix (struct gmesh*,int /*<<< orphan*/ *,char**,char**,char**) ; 
 int efi_hd_to_unix (struct gmesh*,int /*<<< orphan*/ *,char**,char**,char**) ; 
 int efi_zpool_to_unix (struct gmesh*,int /*<<< orphan*/ *,char**,char**,char**) ; 
 int /*<<< orphan*/  geom_deletetree (struct gmesh*) ; 
 scalar_t__ geom_gettree (struct gmesh*) ; 
 scalar_t__ is_cdrom_device (int /*<<< orphan*/ *) ; 
 scalar_t__ is_floppy_device (int /*<<< orphan*/ *) ; 
 scalar_t__ is_zpool_device (int /*<<< orphan*/ *) ; 

int
efivar_device_path_to_unix_path(const_efidp dp, char **dev, char **relpath, char **abspath)
{
	const_efidp walker;
	struct gmesh mesh;
	int rv = 0;

	/*
	 * Sanity check args, fail early
	 */
	if (dp == NULL || dev == NULL || relpath == NULL || abspath == NULL)
		return (EDOOFUS);

	*dev = NULL;
	*relpath = NULL;
	*abspath = NULL;

	/*
	 * Find the first media device path we can. If we go too far,
	 * assume the passed in device path is bogus. If we hit the end
	 * then we didn't find a media device path, so signal that error.
	 */
	walker = dp;
	while (DevicePathType(walker) != MEDIA_DEVICE_PATH &&
	    DevicePathType(walker) != END_DEVICE_PATH_TYPE) {
		walker = (const_efidp)NextDevicePathNode(walker);
		if ((uintptr_t)walker - (uintptr_t)dp > MAX_DP_SANITY)
			return (EINVAL);
	}
	if (DevicePathType(walker) !=  MEDIA_DEVICE_PATH)
		return (EINVAL);

	/*
	 * There's several types of media paths. We're only interested in the
	 * hard disk path, as it's really the only relevant one to booting. The
	 * CD path just might also be relevant, and would be easy to add, but
	 * isn't supported. A file path too is relevant, but at this stage, it's
	 * premature because we're trying to translate a specification for a device
	 * and path on that device into a unix path, or at the very least, a
	 * geom device : path-on-device.
	 *
	 * Also, ZFS throws a bit of a monkey wrench in here since it doesn't have
	 * a device path type (it creates a new virtual device out of one or more
	 * storage devices).
	 *
	 * For all of them, we'll need to know the geoms, so allocate / free the
	 * geom mesh here since it's safer than doing it in each sub-function
	 * which may have many error exits.
	 */
	if (geom_gettree(&mesh))
		return (ENOMEM);

	rv = EINVAL;
	if (DevicePathSubType(walker) == MEDIA_HARDDRIVE_DP)
		rv = efi_hd_to_unix(&mesh, walker, dev, relpath, abspath);
#ifdef notyet
	else if (is_cdrom_device(walker))
		rv = efi_cdrom_to_unix(&mesh, walker, dev, relpath, abspath);
	else if (is_floppy_device(walker))
		rv = efi_floppy_to_unix(&mesh, walker, dev, relpath, abspath);
	else if (is_zpool_device(walker))
		rv = efi_zpool_to_unix(&mesh, walker, dev, relpath, abspath);
#endif
	geom_deletetree(&mesh);

	return (rv);
}