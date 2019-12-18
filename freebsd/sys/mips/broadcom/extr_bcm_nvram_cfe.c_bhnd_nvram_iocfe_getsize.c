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
struct bcm_nvram_iocfe {size_t size; } ;

/* Variables and functions */

__attribute__((used)) static size_t
bhnd_nvram_iocfe_getsize(struct bhnd_nvram_io *io)
{
	struct bcm_nvram_iocfe	*iocfe = (struct bcm_nvram_iocfe *)io;
	return (iocfe->size);
}