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
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  dir; } ;
struct cb_file {TYPE_1__ cf_u; scalar_t__ cf_isdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cb_file*) ; 

__attribute__((used)) static int
cb_close(void *arg, void *h)
{
	struct cb_file *cf = h;

	if (cf->cf_isdir)
		closedir(cf->cf_u.dir);
	else
		close(cf->cf_u.fd);
	free(cf);

	return (0);
}