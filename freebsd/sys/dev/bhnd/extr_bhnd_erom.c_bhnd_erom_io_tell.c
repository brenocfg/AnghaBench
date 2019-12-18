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
struct bhnd_erom_io {int (* tell ) (struct bhnd_erom_io*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  bhnd_size_t ;
typedef  int /*<<< orphan*/  bhnd_addr_t ;

/* Variables and functions */
 int stub1 (struct bhnd_erom_io*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
bhnd_erom_io_tell(struct bhnd_erom_io *eio, bhnd_addr_t *addr,
    bhnd_size_t *size)
{
	return (eio->tell(eio, addr, size));
}