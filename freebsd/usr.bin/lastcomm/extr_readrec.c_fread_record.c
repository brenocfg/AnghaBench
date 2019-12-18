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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EFTYPE ; 
 int EOF ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fread_record(void *ptr, size_t size, FILE *f)
{
	size_t rv;

	if ((rv = fread(ptr, 1, size, f)) == size)
		return (0);
	else if (ferror(f) || rv == 0)
		return (EOF);
	else {
		/* Short read. */
		errno = EFTYPE;
		return (EOF);
	}
}