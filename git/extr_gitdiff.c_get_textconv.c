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
struct userdiff_driver {int dummy; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct diff_filespec {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FILE_VALID (struct diff_filespec*) ; 
 int /*<<< orphan*/  diff_filespec_load_driver (struct diff_filespec*,int /*<<< orphan*/ ) ; 
 struct userdiff_driver* userdiff_get_textconv (struct repository*,int /*<<< orphan*/ ) ; 

struct userdiff_driver *get_textconv(struct repository *r,
				     struct diff_filespec *one)
{
	if (!DIFF_FILE_VALID(one))
		return NULL;

	diff_filespec_load_driver(one, r->index);
	return userdiff_get_textconv(r, one->driver);
}