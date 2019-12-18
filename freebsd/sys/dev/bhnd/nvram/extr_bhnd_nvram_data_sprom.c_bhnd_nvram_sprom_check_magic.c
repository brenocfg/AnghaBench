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
typedef  scalar_t__ uint16_t ;
struct bhnd_nvram_io {int dummy; } ;
struct TYPE_3__ {int flags; scalar_t__ magic_value; int /*<<< orphan*/  magic_offset; } ;
typedef  TYPE_1__ bhnd_sprom_layout ;

/* Variables and functions */
 int ENXIO ; 
 int SPROM_LAYOUT_MAGIC_NONE ; 
 int bhnd_nvram_io_read (struct bhnd_nvram_io*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ le16toh (scalar_t__) ; 

__attribute__((used)) static int
bhnd_nvram_sprom_check_magic(struct bhnd_nvram_io *io,
    const bhnd_sprom_layout *layout, uint16_t *magic)
{
	int error;

	/* Skip if layout does not define a magic value */
	if (layout->flags & SPROM_LAYOUT_MAGIC_NONE)
		return (0);

	/* Read the magic value */
	error = bhnd_nvram_io_read(io, layout->magic_offset, magic,
	    sizeof(*magic));
	if (error)
		return (error);

	*magic = le16toh(*magic);

	/* If the signature does not match, skip to next layout */
	if (*magic != layout->magic_value)
		return (ENXIO);

	return (0);
}