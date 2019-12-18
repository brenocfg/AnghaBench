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
struct pfr_tstats {int dummy; } ;
struct pfr_table {int dummy; } ;
struct pfioc_table {int pfrio_flags; int pfrio_esize; int pfrio_size; struct pfr_tstats* pfrio_buffer; struct pfr_table pfrio_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCRGETTSTATS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  bzero (struct pfioc_table*,int) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_table*) ; 

int
pfr_get_tstats(struct pfr_table *filter, struct pfr_tstats *tbl, int *size,
	int flags)
{
	struct pfioc_table io;

	if (size == NULL || *size < 0 || (*size && tbl == NULL)) {
		errno = EINVAL;
		return (-1);
	}
	bzero(&io, sizeof io);
	io.pfrio_flags = flags;
	if (filter != NULL)
		io.pfrio_table = *filter;
	io.pfrio_buffer = tbl;
	io.pfrio_esize = sizeof(*tbl);
	io.pfrio_size = *size;
	if (ioctl(dev, DIOCRGETTSTATS, &io))
		return (-1);
	*size = io.pfrio_size;
	return (0);
}