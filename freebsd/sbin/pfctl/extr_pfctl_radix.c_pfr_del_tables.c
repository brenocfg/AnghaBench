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
struct pfr_table {int dummy; } ;
struct pfioc_table {int pfrio_flags; int pfrio_esize; int pfrio_size; int pfrio_ndel; struct pfr_table* pfrio_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCRDELTABLES ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  bzero (struct pfioc_table*,int) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_table*) ; 

int
pfr_del_tables(struct pfr_table *tbl, int size, int *ndel, int flags)
{
	struct pfioc_table io;

	if (size < 0 || (size && tbl == NULL)) {
		errno = EINVAL;
		return (-1);
	}
	bzero(&io, sizeof io);
	io.pfrio_flags = flags;
	io.pfrio_buffer = tbl;
	io.pfrio_esize = sizeof(*tbl);
	io.pfrio_size = size;
	if (ioctl(dev, DIOCRDELTABLES, &io))
		return (-1);
	if (ndel != NULL)
		*ndel = io.pfrio_ndel;
	return (0);
}