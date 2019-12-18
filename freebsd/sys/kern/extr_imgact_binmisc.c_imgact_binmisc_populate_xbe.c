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
struct TYPE_6__ {char* xbe_interpreter; char* xbe_magic; char* xbe_mask; int xbe_msize; int /*<<< orphan*/  xbe_moffset; int /*<<< orphan*/  xbe_flags; int /*<<< orphan*/  xbe_version; int /*<<< orphan*/  xbe_name; } ;
typedef  TYPE_1__ ximgact_binmisc_entry_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int ibe_interp_length; int ibe_msize; int /*<<< orphan*/  ibe_moffset; int /*<<< orphan*/  ibe_flags; int /*<<< orphan*/  ibe_mask; int /*<<< orphan*/  ibe_magic; int /*<<< orphan*/  ibe_interpreter; int /*<<< orphan*/  ibe_name; } ;
typedef  TYPE_2__ imgact_binmisc_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBE_NAME_MAX ; 
 int /*<<< orphan*/  IBE_VERSION ; 
 int /*<<< orphan*/  SA_LOCKED ; 
 int /*<<< orphan*/  interp_list_sx ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imgact_binmisc_populate_xbe(ximgact_binmisc_entry_t *xbe,
    imgact_binmisc_entry_t *ibe)
{
	uint32_t i;

	sx_assert(&interp_list_sx, SA_LOCKED);

	memset(xbe, 0, sizeof(*xbe));
	strlcpy(xbe->xbe_name, ibe->ibe_name, IBE_NAME_MAX);

	/* Copy interpreter string.  Replace NULL breaks with space. */
	memcpy(xbe->xbe_interpreter, ibe->ibe_interpreter,
	    ibe->ibe_interp_length);
	for(i = 0; i < (ibe->ibe_interp_length - 1); i++)
		if (xbe->xbe_interpreter[i] == '\0')
			xbe->xbe_interpreter[i] = ' ';

	memcpy(xbe->xbe_magic, ibe->ibe_magic, ibe->ibe_msize);
	memcpy(xbe->xbe_mask, ibe->ibe_mask, ibe->ibe_msize);
	xbe->xbe_version = IBE_VERSION;
	xbe->xbe_flags = ibe->ibe_flags;
	xbe->xbe_moffset = ibe->ibe_moffset;
	xbe->xbe_msize = ibe->ibe_msize;

	return (0);
}