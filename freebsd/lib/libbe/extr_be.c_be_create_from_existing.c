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
typedef  int /*<<< orphan*/  libbe_handle_t ;

/* Variables and functions */
 int BE_MAXPATHLEN ; 
 int be_clone (int /*<<< orphan*/ *,char const*,char*,int) ; 
 int be_snapshot (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,char*) ; 
 int set_error (int /*<<< orphan*/ *,int) ; 

int
be_create_from_existing(libbe_handle_t *lbh, const char *bename, const char *old)
{
	int err;
	char snap[BE_MAXPATHLEN];

	if ((err = be_snapshot(lbh, old, NULL, true, snap)) != 0)
		return (set_error(lbh, err));

        err = be_clone(lbh, bename, snap, -1);

	return (set_error(lbh, err));
}