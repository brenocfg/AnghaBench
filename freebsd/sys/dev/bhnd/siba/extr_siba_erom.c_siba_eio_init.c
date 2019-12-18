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
typedef  int /*<<< orphan*/  u_int ;
struct siba_erom_io {int /*<<< orphan*/  ncores; struct bhnd_erom_io* eio; } ;
struct bhnd_erom_io {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
siba_eio_init(struct siba_erom_io *io, struct bhnd_erom_io *eio, u_int ncores)
{
	io->eio = eio;
	io->ncores = ncores;
	return (0);
}