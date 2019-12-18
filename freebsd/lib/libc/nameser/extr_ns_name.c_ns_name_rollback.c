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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */

void
ns_name_rollback(const u_char *src, const u_char **dnptrs,
		 const u_char **lastdnptr)
{
	while (dnptrs < lastdnptr && *dnptrs != NULL) {
		if (*dnptrs >= src) {
			*dnptrs = NULL;
			break;
		}
		dnptrs++;
	}
}