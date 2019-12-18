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
struct bhnd_nvram_io {int dummy; } ;
struct bcm_nvram_iocfe {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfe_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bhnd_nvram_iocfe_free(struct bhnd_nvram_io *io)
{
	struct bcm_nvram_iocfe	*iocfe = (struct bcm_nvram_iocfe *)io;

	/* CFE I/O instances are statically allocated; we do not need to free
	 * the instance itself */
	cfe_close(iocfe->fd);
}