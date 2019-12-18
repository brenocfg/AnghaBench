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
struct crypt_find_op {int crid; char* name; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/ * crypto_find_device_byhid (int) ; 
 int crypto_find_driver (char*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
cryptodev_find(struct crypt_find_op *find)
{
	device_t dev;
	size_t fnlen = sizeof find->name;

	if (find->crid != -1) {
		dev = crypto_find_device_byhid(find->crid);
		if (dev == NULL)
			return (ENOENT);
		strncpy(find->name, device_get_nameunit(dev), fnlen);
		find->name[fnlen - 1] = '\x0';
	} else {
		find->name[fnlen - 1] = '\x0';
		find->crid = crypto_find_driver(find->name);
		if (find->crid == -1)
			return (ENOENT);
	}
	return (0);
}