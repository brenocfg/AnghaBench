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
struct open_file {int /*<<< orphan*/  f_fsdata; int /*<<< orphan*/ * f_dev; } ;

/* Variables and functions */
 int CALLBACK (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  host_dev ; 
 int /*<<< orphan*/  open ; 

__attribute__((used)) static int
host_open(const char *upath, struct open_file *f)
{

	if (f->f_dev != &host_dev)
		return (EINVAL);

	return (CALLBACK(open, upath, &f->f_fsdata));
}