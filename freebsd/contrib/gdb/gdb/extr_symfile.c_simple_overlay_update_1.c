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
struct obj_section {scalar_t__ ovly_mapped; int /*<<< orphan*/ * the_bfd_section; TYPE_1__* objfile; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {int /*<<< orphan*/ * obfd; } ;

/* Variables and functions */
 size_t LMA ; 
 size_t MAPPED ; 
 int TARGET_LONG_BYTES ; 
 size_t VMA ; 
 int bfd_get_section_size (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_section_lma (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cache_novlys ; 
 scalar_t__** cache_ovly_table ; 
 scalar_t__ cache_ovly_table_base ; 
 int /*<<< orphan*/  read_target_long_array (scalar_t__,int*,int) ; 

__attribute__((used)) static int
simple_overlay_update_1 (struct obj_section *osect)
{
  int i, size;
  bfd *obfd = osect->objfile->obfd;
  asection *bsect = osect->the_bfd_section;

  size = bfd_get_section_size (osect->the_bfd_section);
  for (i = 0; i < cache_novlys; i++)
    if (cache_ovly_table[i][VMA] == bfd_section_vma (obfd, bsect)
	&& cache_ovly_table[i][LMA] == bfd_section_lma (obfd, bsect)
	/* && cache_ovly_table[i][SIZE] == size */ )
      {
	read_target_long_array (cache_ovly_table_base + i * TARGET_LONG_BYTES,
				(int *) cache_ovly_table[i], 4);
	if (cache_ovly_table[i][VMA] == bfd_section_vma (obfd, bsect)
	    && cache_ovly_table[i][LMA] == bfd_section_lma (obfd, bsect)
	    /* && cache_ovly_table[i][SIZE] == size */ )
	  {
	    osect->ovly_mapped = cache_ovly_table[i][MAPPED];
	    return 1;
	  }
	else	/* Warning!  Warning!  Target's ovly table has changed! */
	  return 0;
      }
  return 0;
}