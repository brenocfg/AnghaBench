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
struct mkimg_format {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mkimg_format* format ; 
 struct mkimg_format* format_iterate (struct mkimg_format*) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

int
format_select(const char *spec)
{
	struct mkimg_format *f;

	f = NULL;
	while ((f = format_iterate(f)) != NULL) {
		if (strcasecmp(spec, f->name) == 0) {
			format = f;
			return (0);
		}
	}
	return (EINVAL);
}