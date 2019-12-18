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
struct nameidata {int dummy; } ;

/* Variables and functions */
 int FREAD ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  pwd_ensure_dirs () ; 
 int vn_open (struct nameidata*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
open_file(const char *path, struct nameidata *nid)
{
	int flags, rc;

	flags = FREAD;

	pwd_ensure_dirs();

	NDINIT(nid, LOOKUP, 0, UIO_SYSSPACE, path, curthread);
	rc = vn_open(nid, &flags, 0, NULL);
	NDFREE(nid, NDF_ONLY_PNBUF);
	if (rc != 0)
		return (rc);

	return (0);
}