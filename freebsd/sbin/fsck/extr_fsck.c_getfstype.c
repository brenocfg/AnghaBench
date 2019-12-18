#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  str; } ;
struct diocgattr_arg {int len; TYPE_2__ value; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {char const* name; int /*<<< orphan*/ * ptype; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGATTR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct diocgattr_arg*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ptype_map ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
getfstype(const char *str)
{
	struct diocgattr_arg attr;
	int fd, i;

	if ((fd = open(str, O_RDONLY)) == -1)
		err(1, "cannot open `%s'", str);

	strncpy(attr.name, "PART::type", sizeof(attr.name));
	memset(&attr.value, 0, sizeof(attr.value));
	attr.len = sizeof(attr.value);
	if (ioctl(fd, DIOCGATTR, &attr) == -1) {
		(void) close(fd);
		return(NULL);
	}
	(void) close(fd);
	for (i = 0; ptype_map[i].ptype != NULL; i++)
		if (strstr(attr.value.str, ptype_map[i].ptype) != NULL)
			return (ptype_map[i].name);
	return (NULL);
}