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
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,char*,void*,int /*<<< orphan*/ **) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 scalar_t__ zfs_component_namecheck (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dsl_bookmark_hold_ds(dsl_pool_t *dp, const char *fullname,
    dsl_dataset_t **dsp, void *tag, char **shortnamep)
{
	char buf[ZFS_MAX_DATASET_NAME_LEN];
	char *hashp;

	if (strlen(fullname) >= ZFS_MAX_DATASET_NAME_LEN)
		return (SET_ERROR(ENAMETOOLONG));
	hashp = strchr(fullname, '#');
	if (hashp == NULL)
		return (SET_ERROR(EINVAL));

	*shortnamep = hashp + 1;
	if (zfs_component_namecheck(*shortnamep, NULL, NULL))
		return (SET_ERROR(EINVAL));
	(void) strlcpy(buf, fullname, hashp - fullname + 1);
	return (dsl_dataset_hold(dp, buf, tag, dsp));
}