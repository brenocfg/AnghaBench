#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct dirent {size_t d_namlen; int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_fileno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dir; } ;
struct cb_file {TYPE_1__ cf_u; int /*<<< orphan*/  cf_isdir; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 struct dirent* readdir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cb_readdir(void *arg, void *h, uint32_t *fileno_return, uint8_t *type_return,
	   size_t *namelen_return, char *name)
{
	struct cb_file *cf = h;
	struct dirent *dp;

	if (!cf->cf_isdir)
		return (EINVAL);

	dp = readdir(cf->cf_u.dir);
	if (!dp)
		return (ENOENT);

	/*
	 * Note: d_namlen is in the range 0..255 and therefore less
	 * than PATH_MAX so we don't need to test before copying.
	 */
	*fileno_return = dp->d_fileno;
	*type_return = dp->d_type;
	*namelen_return = dp->d_namlen;
	memcpy(name, dp->d_name, dp->d_namlen);
	name[dp->d_namlen] = 0;

	return (0);
}