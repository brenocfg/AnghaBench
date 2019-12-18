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
struct stat {scalar_t__ st_size; } ;
struct TYPE_2__ {scalar_t__ bootcode; } ;

/* Variables and functions */
 int EFBIG ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/ * bootcode ; 
 int errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ read (int,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* scheme ; 

int
scheme_bootcode(int fd)
{
	struct stat sb;

	if (scheme == NULL || scheme->bootcode == 0)
		return (ENXIO);

	if (fstat(fd, &sb) == -1)
		return (errno);
	if (sb.st_size > scheme->bootcode)
		return (EFBIG);

	bootcode = malloc(scheme->bootcode);
	if (bootcode == NULL)
		return (ENOMEM);
	memset(bootcode, 0, scheme->bootcode);
	if (read(fd, bootcode, sb.st_size) != sb.st_size) {
		free(bootcode);
		bootcode = NULL;
		return (errno);
	}
	return (0);
}