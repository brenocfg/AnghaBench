#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct bhnd_erom_io {int dummy; } ;
struct bhnd_chipid {scalar_t__ enum_addr; } ;
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ bhnd_erom_class_t ;

/* Variables and functions */
 int BHND_EROM_INIT (int /*<<< orphan*/ *,struct bhnd_chipid const*,struct bhnd_erom_io*) ; 
 int /*<<< orphan*/  M_BHND ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ kobj_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kobj_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int) ; 

bhnd_erom_t *
bhnd_erom_alloc(bhnd_erom_class_t *cls, const struct bhnd_chipid *cid,
    struct bhnd_erom_io *eio)
{
	bhnd_erom_t	*erom;
	int		 error;

	erom = (bhnd_erom_t *)kobj_create((kobj_class_t)cls, M_BHND,
	    M_WAITOK|M_ZERO);

	if ((error = BHND_EROM_INIT(erom, cid, eio))) {
		printf("error initializing %s parser at %#jx: %d\n", cls->name,
		    (uintmax_t)cid->enum_addr, error);

		kobj_delete((kobj_t)erom, M_BHND);
		return (NULL);
	}

	return (erom);
}