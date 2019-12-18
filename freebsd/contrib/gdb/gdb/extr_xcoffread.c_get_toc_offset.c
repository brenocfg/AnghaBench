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
struct objfile {scalar_t__ sym_private; } ;
struct coff_symfile_info {int /*<<< orphan*/  toc_offset; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */

CORE_ADDR
get_toc_offset (struct objfile *objfile)
{
  if (objfile)
    return ((struct coff_symfile_info *) objfile->sym_private)->toc_offset;
  return 0;
}