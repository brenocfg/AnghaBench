#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfd_section {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
struct TYPE_5__ {scalar_t__ d_ptr; } ;
struct TYPE_8__ {TYPE_1__ d_un; scalar_t__ d_tag; } ;
struct TYPE_6__ {scalar_t__ d_ptr; } ;
struct TYPE_7__ {TYPE_2__ d_un; scalar_t__ d_tag; } ;
typedef  TYPE_3__ Elf64_External_Dyn ;
typedef  TYPE_4__ Elf32_External_Dyn ;
typedef  void* CORE_ADDR ;

/* Variables and functions */
 long DT_DEBUG ; 
 long DT_MIPS_RLD_MAP ; 
 long DT_NULL ; 
 int HOST_CHAR_BIT ; 
 int TARGET_PTR_BIT ; 
 char* alloca (int) ; 
 int bfd_get_arch_size (int /*<<< orphan*/ ) ; 
 struct bfd_section* bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 void* bfd_h_get_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* bfd_h_get_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bfd_section_size (int /*<<< orphan*/ ,struct bfd_section*) ; 
 void* bfd_section_vma (int /*<<< orphan*/ ,struct bfd_section*) ; 
 int /*<<< orphan*/  exec_bfd ; 
 void* extract_unsigned_integer (char*,int) ; 
 scalar_t__ target_read_memory (void*,char*,int) ; 

__attribute__((used)) static CORE_ADDR
elf_locate_base (void)
{
  struct bfd_section *dyninfo_sect;
  int dyninfo_sect_size;
  CORE_ADDR dyninfo_addr;
  char *buf;
  char *bufend;
  int arch_size;

  /* Find the start address of the .dynamic section.  */
  dyninfo_sect = bfd_get_section_by_name (exec_bfd, ".dynamic");
  if (dyninfo_sect == NULL)
    return 0;
  dyninfo_addr = bfd_section_vma (exec_bfd, dyninfo_sect);

  /* Read in .dynamic section, silently ignore errors.  */
  dyninfo_sect_size = bfd_section_size (exec_bfd, dyninfo_sect);
  buf = alloca (dyninfo_sect_size);
  if (target_read_memory (dyninfo_addr, buf, dyninfo_sect_size))
    return 0;

  /* Find the DT_DEBUG entry in the the .dynamic section.
     For mips elf we look for DT_MIPS_RLD_MAP, mips elf apparently has
     no DT_DEBUG entries.  */

  arch_size = bfd_get_arch_size (exec_bfd);
  if (arch_size == -1)	/* failure */
    return 0;

  if (arch_size == 32)
    { /* 32-bit elf */
      for (bufend = buf + dyninfo_sect_size;
	   buf < bufend;
	   buf += sizeof (Elf32_External_Dyn))
	{
	  Elf32_External_Dyn *x_dynp = (Elf32_External_Dyn *) buf;
	  long dyn_tag;
	  CORE_ADDR dyn_ptr;

	  dyn_tag = bfd_h_get_32 (exec_bfd, (bfd_byte *) x_dynp->d_tag);
	  if (dyn_tag == DT_NULL)
	    break;
	  else if (dyn_tag == DT_DEBUG)
	    {
	      dyn_ptr = bfd_h_get_32 (exec_bfd, 
				      (bfd_byte *) x_dynp->d_un.d_ptr);
	      return dyn_ptr;
	    }
	  else if (dyn_tag == DT_MIPS_RLD_MAP)
	    {
	      char *pbuf;
	      int pbuf_size = TARGET_PTR_BIT / HOST_CHAR_BIT;

	      pbuf = alloca (pbuf_size);
	      /* DT_MIPS_RLD_MAP contains a pointer to the address
		 of the dynamic link structure.  */
	      dyn_ptr = bfd_h_get_32 (exec_bfd, 
				      (bfd_byte *) x_dynp->d_un.d_ptr);
	      if (target_read_memory (dyn_ptr, pbuf, pbuf_size))
		return 0;
	      return extract_unsigned_integer (pbuf, pbuf_size);
	    }
	}
    }
  else /* 64-bit elf */
    {
      for (bufend = buf + dyninfo_sect_size;
	   buf < bufend;
	   buf += sizeof (Elf64_External_Dyn))
	{
	  Elf64_External_Dyn *x_dynp = (Elf64_External_Dyn *) buf;
	  long dyn_tag;
	  CORE_ADDR dyn_ptr;

	  dyn_tag = bfd_h_get_64 (exec_bfd, (bfd_byte *) x_dynp->d_tag);
	  if (dyn_tag == DT_NULL)
	    break;
	  else if (dyn_tag == DT_DEBUG)
	    {
	      dyn_ptr = bfd_h_get_64 (exec_bfd, 
				      (bfd_byte *) x_dynp->d_un.d_ptr);
	      return dyn_ptr;
	    }
	  else if (dyn_tag == DT_MIPS_RLD_MAP)
	    {
	      char *pbuf;
	      int pbuf_size = TARGET_PTR_BIT / HOST_CHAR_BIT;

	      pbuf = alloca (pbuf_size);
	      /* DT_MIPS_RLD_MAP contains a pointer to the address
		 of the dynamic link structure.  */
	      dyn_ptr = bfd_h_get_64 (exec_bfd, 
				      (bfd_byte *) x_dynp->d_un.d_ptr);
	      if (target_read_memory (dyn_ptr, pbuf, pbuf_size))
		return 0;
	      return extract_unsigned_integer (pbuf, pbuf_size);
	    }
	}
    }

  /* DT_DEBUG entry not found.  */
  return 0;
}