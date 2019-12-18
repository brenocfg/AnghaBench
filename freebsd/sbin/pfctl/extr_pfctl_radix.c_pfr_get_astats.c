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
struct pfr_astats {int dummy; } ;
struct pfioc_table {int pfrio_flags; int pfrio_esize; int pfrio_size; struct pfr_astats* pfrio_buffer; struct pfr_table pfrio_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCRGETASTATS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  bzero (struct pfioc_table*,int) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_table*) ; 

int
pfr_get_astats(struct pfr_table *tbl, struct pfr_astats *addr, int *size,
    int flags)
{
	struct pfioc_table io;

	if (tbl == NULL || size == NULL || *size < 0 ||
	    (*size && addr == NULL)) {
		errno = EINVAL;
		return (-1);
	}
	bzero(&io, sizeof io);
	io.pfrio_flags = flags;
	io.pfrio_table = *tbl;
	io.pfrio_buffer = addr;
	io.pfrio_esize = sizeof(*addr);
	io.pfrio_size = *size;
	if (ioctl(dev, DIOCRGETASTATS, &io))
		return (-1);
	*size = io.pfrio_size;
	return (0);
}