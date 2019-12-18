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
struct bhnd_erom_iores {TYPE_1__* mapped; } ;
struct bhnd_erom_io {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_size_t ;
typedef  int /*<<< orphan*/  bhnd_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_erom_iores_tell(struct bhnd_erom_io *eio, bhnd_addr_t *addr,
    bhnd_size_t *size)
{
	struct bhnd_erom_iores *iores = (struct bhnd_erom_iores *)eio;

	if (iores->mapped == NULL)
		return (ENXIO);

	*addr = rman_get_start(iores->mapped->res);
	*size = rman_get_size(iores->mapped->res);

	return (0);
}