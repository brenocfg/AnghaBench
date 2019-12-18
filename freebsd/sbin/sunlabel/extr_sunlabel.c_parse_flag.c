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
typedef  void* uint16_t ;
struct tags {scalar_t__ id; int /*<<< orphan*/  name; } ;
struct sun_disklabel {TYPE_1__* sl_vtoc_map; } ;
struct TYPE_2__ {void* svtoc_flag; } ;

/* Variables and functions */
 struct tags* knownflags ; 
 size_t nitems (struct tags*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
parse_flag(struct sun_disklabel *sl, int part, const char *flag)
{
	struct tags *tp;
	char *endp;
	size_t i;
	unsigned long l;

	for (i = 0, tp = knownflags; i < nitems(knownflags); i++, tp++)
		if (strcmp(tp->name, flag) == 0) {
			sl->sl_vtoc_map[part].svtoc_flag = (uint16_t)tp->id;
			return (0);
		}

	l = strtoul(flag, &endp, 0);
	if (*flag != '\0' && *endp == '\0') {
		sl->sl_vtoc_map[part].svtoc_flag = (uint16_t)l;
		return (0);
	}

	return (-1);
}