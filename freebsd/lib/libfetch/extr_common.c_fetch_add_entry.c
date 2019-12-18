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
struct url_stat {int dummy; } ;
struct url_ent {scalar_t__* name; int /*<<< orphan*/  stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fetch_syserr () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct url_stat*,int) ; 
 struct url_ent* reallocarray (struct url_ent*,int,int) ; 
 int /*<<< orphan*/  snprintf (scalar_t__*,int /*<<< orphan*/ ,char*,char const*) ; 

int
fetch_add_entry(struct url_ent **p, int *size, int *len,
    const char *name, struct url_stat *us)
{
	struct url_ent *tmp;

	if (*p == NULL) {
		*size = 0;
		*len = 0;
	}

	if (*len >= *size - 1) {
		tmp = reallocarray(*p, *size * 2 + 1, sizeof(**p));
		if (tmp == NULL) {
			errno = ENOMEM;
			fetch_syserr();
			return (-1);
		}
		*size = (*size * 2 + 1);
		*p = tmp;
	}

	tmp = *p + *len;
	snprintf(tmp->name, PATH_MAX, "%s", name);
	memcpy(&tmp->stat, us, sizeof(*us));

	(*len)++;
	(++tmp)->name[0] = 0;

	return (0);
}