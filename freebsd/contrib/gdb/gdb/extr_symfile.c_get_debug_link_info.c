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
struct objfile {int /*<<< orphan*/  obfd; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 unsigned long bfd_get_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static char *
get_debug_link_info (struct objfile *objfile, unsigned long *crc32_out)
{
  asection *sect;
  bfd_size_type debuglink_size;
  unsigned long crc32;
  char *contents;
  int crc_offset;
  unsigned char *p;
  
  sect = bfd_get_section_by_name (objfile->obfd, ".gnu_debuglink");

  if (sect == NULL)
    return NULL;

  debuglink_size = bfd_section_size (objfile->obfd, sect);
  
  contents = xmalloc (debuglink_size);
  bfd_get_section_contents (objfile->obfd, sect, contents,
			    (file_ptr)0, (bfd_size_type)debuglink_size);

  /* Crc value is stored after the filename, aligned up to 4 bytes. */
  crc_offset = strlen (contents) + 1;
  crc_offset = (crc_offset + 3) & ~3;

  crc32 = bfd_get_32 (objfile->obfd, (bfd_byte *) (contents + crc_offset));
  
  *crc32_out = crc32;
  return contents;
}