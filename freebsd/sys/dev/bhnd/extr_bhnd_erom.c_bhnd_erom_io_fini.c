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
struct bhnd_erom_io {void (* fini ) (struct bhnd_erom_io*) ;} ;

/* Variables and functions */
 void stub1 (struct bhnd_erom_io*) ; 

void
bhnd_erom_io_fini(struct bhnd_erom_io *eio)
{
	if (eio->fini != NULL)
		return (eio->fini(eio));
}