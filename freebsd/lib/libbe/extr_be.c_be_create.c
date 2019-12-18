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
 int /*<<< orphan*/  be_active_path (int /*<<< orphan*/ *) ; 
 int be_create_from_existing (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int set_error (int /*<<< orphan*/ *,int) ; 

int
be_create(libbe_handle_t *lbh, const char *name)
{
	int err;

	err = be_create_from_existing(lbh, name, be_active_path(lbh));

	return (set_error(lbh, err));
}