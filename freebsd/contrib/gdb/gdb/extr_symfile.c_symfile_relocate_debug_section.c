#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int SEC_DEBUGGING ; 
 int SEC_RELOC ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_simple_get_relocated_section_contents (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symfile_dummy_outputs ; 

bfd_byte *
symfile_relocate_debug_section (bfd *abfd, asection *sectp, bfd_byte *buf)
{
  /* We're only interested in debugging sections with relocation
     information.  */
  if ((sectp->flags & SEC_RELOC) == 0)
    return NULL;
  if ((sectp->flags & SEC_DEBUGGING) == 0)
    return NULL;

  /* We will handle section offsets properly elsewhere, so relocate as if
     all sections begin at 0.  */
  bfd_map_over_sections (abfd, symfile_dummy_outputs, NULL);

  return bfd_simple_get_relocated_section_contents (abfd, sectp, buf, NULL);
}