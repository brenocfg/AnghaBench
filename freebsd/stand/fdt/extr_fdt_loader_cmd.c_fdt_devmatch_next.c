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
struct fdt_property {char const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fdt_apply_overlays () ; 
 struct fdt_property* fdt_get_property (int /*<<< orphan*/ *,int,char*,int*) ; 
 int fdt_next_node (int /*<<< orphan*/ *,int,int*) ; 
 int fdt_path_offset (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fdt_setup_fdtp () ; 
 int /*<<< orphan*/ * fdtp ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

const char *
fdt_devmatch_next(int *tag, int *compatlen)
{
	const struct fdt_property *p;
	const struct fdt_property *status;
	int o, len = -1;
	static int depth = 0;

	if (fdtp == NULL) {
		fdt_setup_fdtp();
		fdt_apply_overlays();
	}

	if (*tag != 0) {
		o = *tag;
		/* We are at the end of the DTB */
		if (o < 0)
			return (NULL);
	} else {
		o = fdt_path_offset(fdtp, "/");
		if (o < 0) {
			printf("Can't find dtb\n");
			return (NULL);
		}
		depth = 0;
	}

	/* Find the next node with a compatible property */
	while (1) {
		p = NULL;
		if (o >= 0 && depth >= 0) {
			/* skip disabled nodes */
			status = fdt_get_property(fdtp, o, "status", &len);
			if (len > 0) {
				if (strcmp(status->data, "disabled") == 0) {
					o = fdt_next_node(fdtp, o, &depth);
					if (o < 0) /* End of tree */
						return (NULL);
					continue;
				}
			}

			p = fdt_get_property(fdtp, o, "compatible", &len);
		}
		if (p)
			break;
		o = fdt_next_node(fdtp, o, &depth);
		if (o < 0) /* End of tree */
			return (NULL);
	}

	/* Prepare next node for next call */
	o = fdt_next_node(fdtp, o, &depth);
	*tag = o;

	if (len >= 0) {
		*compatlen = len;
		return (p->data);
	}
	return (NULL);
}