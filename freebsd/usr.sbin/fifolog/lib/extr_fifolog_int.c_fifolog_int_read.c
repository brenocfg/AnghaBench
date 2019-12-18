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
struct fifolog_file {int logsize; int recsize; int /*<<< orphan*/  recbuf; int /*<<< orphan*/  fd; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  fifolog_int_file_assert (struct fifolog_file const*) ; 
 int pread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int
fifolog_int_read(const struct fifolog_file *ff, off_t recno)
{
	int i;

	fifolog_int_file_assert(ff);
	if (recno >= ff->logsize)
		return (-1);
	recno++;			/* label sector */
	i = pread(ff->fd, ff->recbuf, ff->recsize, recno * ff->recsize);
	if (i < 0)
		return (-2);
	if (i != (int)ff->recsize)
		return (-3);
	return (0);
}