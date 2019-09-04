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
struct index_state {int dummy; } ;
struct diff_filespec {scalar_t__ driver; int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ userdiff_find_by_name (char*) ; 
 scalar_t__ userdiff_find_by_path (struct index_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void diff_filespec_load_driver(struct diff_filespec *one,
				      struct index_state *istate)
{
	/* Use already-loaded driver */
	if (one->driver)
		return;

	if (S_ISREG(one->mode))
		one->driver = userdiff_find_by_path(istate, one->path);

	/* Fallback to default settings */
	if (!one->driver)
		one->driver = userdiff_find_by_name("default");
}