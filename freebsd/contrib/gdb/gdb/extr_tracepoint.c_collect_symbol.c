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
struct symbol {int dummy; } ;
struct collection_list {int dummy; } ;
typedef  void* bfd_signed_vma ;

/* Variables and functions */
 unsigned long DEPRECATED_REGISTER_RAW_SIZE (unsigned int) ; 
 unsigned int DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
#define  LOC_ARG 140 
#define  LOC_BASEREG 139 
#define  LOC_BASEREG_ARG 138 
#define  LOC_CONST 137 
#define  LOC_LOCAL 136 
#define  LOC_LOCAL_ARG 135 
#define  LOC_OPTIMIZED_OUT 134 
#define  LOC_REF_ARG 133 
#define  LOC_REGISTER 132 
#define  LOC_REGPARM 131 
#define  LOC_REGPARM_ADDR 130 
#define  LOC_STATIC 129 
#define  LOC_UNRESOLVED 128 
 unsigned int SYMBOL_BASEREG (struct symbol*) ; 
 int SYMBOL_CLASS (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 void* SYMBOL_VALUE (struct symbol*) ; 
 void* SYMBOL_VALUE_ADDRESS (struct symbol*) ; 
 int /*<<< orphan*/  TYPE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CODE_FLT ; 
 unsigned long TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_memrange (struct collection_list*,unsigned int,void*,unsigned long) ; 
 int /*<<< orphan*/  add_register (struct collection_list*,unsigned int) ; 
 int /*<<< orphan*/  check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info_verbose ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  printf_vma (void*) ; 
 int /*<<< orphan*/  sprintf_vma (char*,void*) ; 

__attribute__((used)) static void
collect_symbol (struct collection_list *collect, struct symbol *sym,
		long frame_regno, long frame_offset)
{
  unsigned long len;
  unsigned int reg;
  bfd_signed_vma offset;

  len = TYPE_LENGTH (check_typedef (SYMBOL_TYPE (sym)));
  switch (SYMBOL_CLASS (sym))
    {
    default:
      printf_filtered ("%s: don't know symbol class %d\n",
		       DEPRECATED_SYMBOL_NAME (sym), SYMBOL_CLASS (sym));
      break;
    case LOC_CONST:
      printf_filtered ("constant %s (value %ld) will not be collected.\n",
		       DEPRECATED_SYMBOL_NAME (sym), SYMBOL_VALUE (sym));
      break;
    case LOC_STATIC:
      offset = SYMBOL_VALUE_ADDRESS (sym);
      if (info_verbose)
	{
	  char tmp[40];

	  sprintf_vma (tmp, offset);
	  printf_filtered ("LOC_STATIC %s: collect %ld bytes at %s.\n",
			   DEPRECATED_SYMBOL_NAME (sym), len, tmp /* address */);
	}
      add_memrange (collect, -1, offset, len);	/* 0 == memory */
      break;
    case LOC_REGISTER:
    case LOC_REGPARM:
      reg = SYMBOL_VALUE (sym);
      if (info_verbose)
	printf_filtered ("LOC_REG[parm] %s: ", DEPRECATED_SYMBOL_NAME (sym));
      add_register (collect, reg);
      /* check for doubles stored in two registers */
      /* FIXME: how about larger types stored in 3 or more regs? */
      if (TYPE_CODE (SYMBOL_TYPE (sym)) == TYPE_CODE_FLT &&
	  len > DEPRECATED_REGISTER_RAW_SIZE (reg))
	add_register (collect, reg + 1);
      break;
    case LOC_REF_ARG:
      printf_filtered ("Sorry, don't know how to do LOC_REF_ARG yet.\n");
      printf_filtered ("       (will not collect %s)\n",
		       DEPRECATED_SYMBOL_NAME (sym));
      break;
    case LOC_ARG:
      reg = frame_regno;
      offset = frame_offset + SYMBOL_VALUE (sym);
      if (info_verbose)
	{
	  printf_filtered ("LOC_LOCAL %s: Collect %ld bytes at offset ",
			   DEPRECATED_SYMBOL_NAME (sym), len);
	  printf_vma (offset);
	  printf_filtered (" from frame ptr reg %d\n", reg);
	}
      add_memrange (collect, reg, offset, len);
      break;
    case LOC_REGPARM_ADDR:
      reg = SYMBOL_VALUE (sym);
      offset = 0;
      if (info_verbose)
	{
	  printf_filtered ("LOC_REGPARM_ADDR %s: Collect %ld bytes at offset ",
			   DEPRECATED_SYMBOL_NAME (sym), len);
	  printf_vma (offset);
	  printf_filtered (" from reg %d\n", reg);
	}
      add_memrange (collect, reg, offset, len);
      break;
    case LOC_LOCAL:
    case LOC_LOCAL_ARG:
      reg = frame_regno;
      offset = frame_offset + SYMBOL_VALUE (sym);
      if (info_verbose)
	{
	  printf_filtered ("LOC_LOCAL %s: Collect %ld bytes at offset ",
			   DEPRECATED_SYMBOL_NAME (sym), len);
	  printf_vma (offset);
	  printf_filtered (" from frame ptr reg %d\n", reg);
	}
      add_memrange (collect, reg, offset, len);
      break;
    case LOC_BASEREG:
    case LOC_BASEREG_ARG:
      reg = SYMBOL_BASEREG (sym);
      offset = SYMBOL_VALUE (sym);
      if (info_verbose)
	{
	  printf_filtered ("LOC_BASEREG %s: collect %ld bytes at offset ",
			   DEPRECATED_SYMBOL_NAME (sym), len);
	  printf_vma (offset);
	  printf_filtered (" from basereg %d\n", reg);
	}
      add_memrange (collect, reg, offset, len);
      break;
    case LOC_UNRESOLVED:
      printf_filtered ("Don't know LOC_UNRESOLVED %s\n", DEPRECATED_SYMBOL_NAME (sym));
      break;
    case LOC_OPTIMIZED_OUT:
      printf_filtered ("%s has been optimized out of existence.\n",
		       DEPRECATED_SYMBOL_NAME (sym));
      break;
    }
}