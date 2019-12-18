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
struct mkimg_scheme {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mkimg_scheme* scheme ; 
 struct mkimg_scheme* scheme_iterate (struct mkimg_scheme*) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

int
scheme_select(const char *spec)
{
	struct mkimg_scheme *s;

	s = NULL;
	while ((s = scheme_iterate(s)) != NULL) {
		if (strcasecmp(spec, s->name) == 0) {
			scheme = s;
			return (0);
		}
	}
	return (EINVAL);
}