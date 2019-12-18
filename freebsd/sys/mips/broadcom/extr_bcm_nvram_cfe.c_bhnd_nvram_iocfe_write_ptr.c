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

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int
bhnd_nvram_iocfe_write_ptr(struct bhnd_nvram_io *io, size_t offset,
    void **ptr, size_t nbytes, size_t *navail)
{
	/* unsupported */
	return (ENODEV);
}