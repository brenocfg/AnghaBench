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
struct coff_symfile_info {scalar_t__ min_lineno_offset; scalar_t__ max_lineno_offset; } ;
struct bfd_section {int lineno_count; scalar_t__ line_filepos; int /*<<< orphan*/  name; } ;
struct bfd {int dummy; } ;
typedef  scalar_t__ file_ptr ;
struct TYPE_2__ {int local_linesz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_STREQ (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* coff_data (struct bfd*) ; 

__attribute__((used)) static void
find_linenos (struct bfd *abfd, struct bfd_section *asect, void *vpinfo)
{
  struct coff_symfile_info *info;
  int size, count;
  file_ptr offset, maxoff;

  count = asect->lineno_count;

  if (!DEPRECATED_STREQ (asect->name, ".text") || count == 0)
    return;

  size = count * coff_data (abfd)->local_linesz;
  info = (struct coff_symfile_info *) vpinfo;
  offset = asect->line_filepos;
  maxoff = offset + size;

  if (offset < info->min_lineno_offset || info->min_lineno_offset == 0)
    info->min_lineno_offset = offset;

  if (maxoff > info->max_lineno_offset)
    info->max_lineno_offset = maxoff;
}