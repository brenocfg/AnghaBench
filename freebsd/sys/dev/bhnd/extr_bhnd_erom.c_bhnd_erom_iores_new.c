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
struct bhnd_erom_io {int /*<<< orphan*/  fini; int /*<<< orphan*/  read; int /*<<< orphan*/  tell; int /*<<< orphan*/  map; } ;
struct bhnd_erom_iores {int owner_rid; int mapped_rid; struct bhnd_erom_io eio; int /*<<< orphan*/ * mapped; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bhnd_erom_iores_fini ; 
 int /*<<< orphan*/  bhnd_erom_iores_map ; 
 int /*<<< orphan*/  bhnd_erom_iores_read ; 
 int /*<<< orphan*/  bhnd_erom_iores_tell ; 
 struct bhnd_erom_iores* malloc (int,int /*<<< orphan*/ ,int) ; 

struct bhnd_erom_io *
bhnd_erom_iores_new(device_t dev, int rid)
{
	struct bhnd_erom_iores	*iores;

	iores = malloc(sizeof(*iores), M_BHND, M_WAITOK | M_ZERO);
	iores->eio.map = bhnd_erom_iores_map;
	iores->eio.tell = bhnd_erom_iores_tell;
	iores->eio.read = bhnd_erom_iores_read;
	iores->eio.fini = bhnd_erom_iores_fini;

	iores->owner = dev;
	iores->owner_rid = rid;
	iores->mapped = NULL;
	iores->mapped_rid = -1;

	return (&iores->eio);
}