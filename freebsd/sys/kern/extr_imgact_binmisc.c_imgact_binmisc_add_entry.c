#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ xbe_msize; char* xbe_name; char* xbe_interpreter; } ;
typedef  TYPE_1__ ximgact_binmisc_entry_t ;
typedef  int /*<<< orphan*/  imgact_binmisc_entry_t ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int IBE_INTERP_LEN_MAX ; 
 scalar_t__ IBE_MAGIC_MAX ; 
 int IBE_NAME_MAX ; 
#define  ISM_OLD_ARGV0 129 
#define  ISM_POUND 128 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * imgact_binmisc_find_entry (char*) ; 
 int /*<<< orphan*/ * imgact_binmisc_new_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  interp_list_entry_count ; 
 int /*<<< orphan*/  interp_list_sx ; 
 int /*<<< orphan*/  interpreter_list ; 
 int /*<<< orphan*/  isascii (int) ; 
 int /*<<< orphan*/  link ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
imgact_binmisc_add_entry(ximgact_binmisc_entry_t *xbe)
{
	imgact_binmisc_entry_t *ibe;
	char *p;
	int cnt;

	if (xbe->xbe_msize > IBE_MAGIC_MAX)
		return (EINVAL);

	for(cnt = 0, p = xbe->xbe_name; *p != 0; cnt++, p++)
		if (cnt >= IBE_NAME_MAX || !isascii((int)*p))
			return (EINVAL);

	for(cnt = 0, p = xbe->xbe_interpreter; *p != 0; cnt++, p++)
		if (cnt >= IBE_INTERP_LEN_MAX || !isascii((int)*p))
			return (EINVAL);

	/* Make sure we don't have any invalid #'s. */
	p = xbe->xbe_interpreter;
	while (1) {
		p = strchr(p, '#');
		if (!p)
			break;

		p++;
		switch(*p) {
		case ISM_POUND:
			/* "##" */
			p++;
			break;

		case ISM_OLD_ARGV0:
			/* "#a" */
			p++;
			break;

		case 0:
		default:
			/* Anything besides the above is invalid. */
			return (EINVAL);
		}
	}

	sx_xlock(&interp_list_sx);
	if (imgact_binmisc_find_entry(xbe->xbe_name) != NULL) {
		sx_xunlock(&interp_list_sx);
		return (EEXIST);
	}

	/* Preallocate a new entry. */
	ibe = imgact_binmisc_new_entry(xbe);

	SLIST_INSERT_HEAD(&interpreter_list, ibe, link);
	interp_list_entry_count++;
	sx_xunlock(&interp_list_sx);

	return (0);
}