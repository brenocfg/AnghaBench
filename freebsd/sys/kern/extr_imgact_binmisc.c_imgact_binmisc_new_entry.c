#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t xbe_msize; int /*<<< orphan*/  xbe_flags; int /*<<< orphan*/  xbe_moffset; int /*<<< orphan*/  xbe_mask; int /*<<< orphan*/  xbe_magic; int /*<<< orphan*/  xbe_interpreter; int /*<<< orphan*/  xbe_name; } ;
typedef  TYPE_1__ ximgact_binmisc_entry_t ;
struct TYPE_7__ {size_t ibe_msize; int /*<<< orphan*/  ibe_flags; int /*<<< orphan*/  ibe_moffset; void* ibe_mask; void* ibe_magic; void* ibe_name; } ;
typedef  TYPE_2__ imgact_binmisc_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBE_NAME_MAX ; 
 int /*<<< orphan*/  M_BINMISC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  imgact_binmisc_populate_interp (int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 size_t min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static imgact_binmisc_entry_t *
imgact_binmisc_new_entry(ximgact_binmisc_entry_t *xbe)
{
	imgact_binmisc_entry_t *ibe = NULL;
	size_t namesz = min(strlen(xbe->xbe_name) + 1, IBE_NAME_MAX);

	ibe = malloc(sizeof(*ibe), M_BINMISC, M_WAITOK|M_ZERO);

	ibe->ibe_name = malloc(namesz, M_BINMISC, M_WAITOK|M_ZERO);
	strlcpy(ibe->ibe_name, xbe->xbe_name, namesz);

	imgact_binmisc_populate_interp(xbe->xbe_interpreter, ibe);

	ibe->ibe_magic = malloc(xbe->xbe_msize, M_BINMISC, M_WAITOK|M_ZERO);
	memcpy(ibe->ibe_magic, xbe->xbe_magic, xbe->xbe_msize);

	ibe->ibe_mask = malloc(xbe->xbe_msize, M_BINMISC, M_WAITOK|M_ZERO);
	memcpy(ibe->ibe_mask, xbe->xbe_mask, xbe->xbe_msize);

	ibe->ibe_moffset = xbe->xbe_moffset;
	ibe->ibe_msize = xbe->xbe_msize;
	ibe->ibe_flags = xbe->xbe_flags;

	return (ibe);
}