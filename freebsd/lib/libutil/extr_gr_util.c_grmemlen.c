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
struct group {char const* gr_name; char const* gr_passwd; char const** gr_mem; } ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static size_t
grmemlen(const struct group *gr, const char *name, int *num_mem)
{
	size_t len;
	int i;

	if (gr == NULL)
		return (0);
	/* Calculate size of the group. */
	len = sizeof(*gr);
	if (gr->gr_name != NULL)
		len += strlen(gr->gr_name) + 1;
	if (gr->gr_passwd != NULL)
		len += strlen(gr->gr_passwd) + 1;
	i = 0;
	if (gr->gr_mem != NULL) {
		for (; gr->gr_mem[i] != NULL; i++) {
			len += strlen(gr->gr_mem[i]) + 1;
			len += sizeof(*gr->gr_mem);
		}
	}
	if (name != NULL) {
		i++;
		len += strlen(name) + 1;
		len += sizeof(*gr->gr_mem);
	}
	/* Allow for NULL pointer */
	if (i != 0)
		len += sizeof(*gr->gr_mem);
	*num_mem = i;
	return(len);
}