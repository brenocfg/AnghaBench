#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_id_t ;
struct TYPE_3__ {int dtargd_ndx; int /*<<< orphan*/  dtargd_native; } ;
typedef  TYPE_1__ dtrace_argdesc_t ;

/* Variables and functions */
 int DTRACE_ARGNONE ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
dtmalloc_getargdesc(void *arg, dtrace_id_t id, void *parg, dtrace_argdesc_t *desc)
{
	const char *p = NULL;

	switch (desc->dtargd_ndx) {
	case 0:
		p = "struct malloc_type *";
		break;
	case 1:
		p = "struct malloc_type_internal *";
		break;
	case 2:
		p = "struct malloc_type_stats *";
		break;
	case 3:
		p = "unsigned long";
		break;
	case 4:
		p = "int";
		break;
	default:
		desc->dtargd_ndx = DTRACE_ARGNONE;
		break;
	}

	if (p != NULL)
		strlcpy(desc->dtargd_native, p, sizeof(desc->dtargd_native));

	return;
}