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
struct section_table {int /*<<< orphan*/  endaddr; int /*<<< orphan*/  addr; } ;
struct section_addr_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int bfd_count_sections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ bfd_get_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct section_addr_info* build_section_addr_info_from_section_table (struct section_table*,struct section_table*) ; 
 int /*<<< orphan*/  build_section_table (int /*<<< orphan*/ *,struct section_table**,struct section_table**) ; 
 int /*<<< orphan*/  xfree (struct section_table*) ; 

__attribute__((used)) static struct section_addr_info *
get_relocated_section_addrs (bfd *abfd, CORE_ADDR text_load)
{
  struct section_addr_info *result = NULL;
  int section_count = bfd_count_sections (abfd);
  asection *text_section = bfd_get_section_by_name (abfd, ".text");
  CORE_ADDR text_vma;

  if (!text_section)
    {
      /* Couldn't get the .text section. Weird. */
    }

  else if (text_load == (text_vma = bfd_get_section_vma (abfd, text_section)))
    {
      /* DLL wasn't relocated. */
    }

  else
    {
      /* Figure out all sections' loaded addresses. The offset here is
	 such that taking a bfd_get_section_vma() result and adding
	 offset will give the real load address of the section. */

      CORE_ADDR offset = text_load - text_vma;

      struct section_table *table_start = NULL;
      struct section_table *table_end = NULL;
      struct section_table *iter = NULL;

      build_section_table (abfd, &table_start, &table_end);

      for (iter = table_start; iter < table_end; ++iter)
	{
	  /* Relocated addresses. */
	  iter->addr += offset;
	  iter->endaddr += offset;
	}

      result = build_section_addr_info_from_section_table (table_start,
							   table_end);

      xfree (table_start);
    }

  return result;
}