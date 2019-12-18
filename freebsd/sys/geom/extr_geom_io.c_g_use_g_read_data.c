#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct g_consumer {TYPE_1__* provider; } ;
typedef  int off_t ;
struct TYPE_2__ {int sectorsize; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 void* g_read_data (struct g_consumer*,int,int,int /*<<< orphan*/ *) ; 

int
g_use_g_read_data(void *devfd, off_t loc, void **bufp, int size)
{
	struct g_consumer *cp;

	KASSERT(*bufp == NULL,
	    ("g_use_g_read_data: non-NULL *bufp %p\n", *bufp));

	cp = (struct g_consumer *)devfd;
	/*
	 * Take care not to issue an invalid I/O request. The offset of
	 * the superblock candidate must be multiples of the provider's
	 * sector size, otherwise an FFS can't exist on the provider
	 * anyway.
	 */
	if (loc % cp->provider->sectorsize != 0)
		return (ENOENT);
	*bufp = g_read_data(cp, loc, size, NULL);
	if (*bufp == NULL)
		return (ENOENT);
	return (0);
}