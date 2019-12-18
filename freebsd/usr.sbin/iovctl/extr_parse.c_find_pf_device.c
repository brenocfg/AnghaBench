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
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  int /*<<< orphan*/ * ucl_object_iter_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/ * ucl_iterate_object (int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int) ; 
 char* ucl_object_key (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ucl_object_tostring_safe (int /*<<< orphan*/  const*,char const**) ; 

__attribute__((used)) static const char *
find_pf_device(const ucl_object_t *pf)
{
	ucl_object_iter_t it;
	const ucl_object_t *obj;
	const char *key, *device;

	it = NULL;
	while ((obj = ucl_iterate_object(pf, &it, true)) != NULL) {
		key = ucl_object_key(obj);

		if (strcasecmp(key, "device") == 0) {
			if (!ucl_object_tostring_safe(obj, &device))
				err(1,
				    "Config PF.device must be a string");

			return (device);
		}
	}

	return (NULL);
}