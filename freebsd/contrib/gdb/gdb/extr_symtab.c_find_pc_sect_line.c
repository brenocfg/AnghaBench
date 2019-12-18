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
struct symtab_and_line {scalar_t__ pc; scalar_t__ line; scalar_t__ end; struct bfd_section* section; struct symtab* symtab; } ;
struct symtab {struct symtab* next; } ;
struct minimal_symbol {int dummy; } ;
struct linetable_entry {scalar_t__ pc; scalar_t__ line; } ;
struct linetable {int nitems; struct linetable_entry* item; } ;
struct blockvector {int dummy; } ;
struct bfd_section {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct blockvector* BLOCKVECTOR (struct symtab*) ; 
 int /*<<< orphan*/  BLOCKVECTOR_BLOCK (struct blockvector*,int /*<<< orphan*/ ) ; 
 void* BLOCK_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLOBAL_BLOCK ; 
 struct linetable* LINETABLE (struct symtab*) ; 
 scalar_t__ MSYMBOL_TYPE (struct minimal_symbol*) ; 
 int /*<<< orphan*/  SYMBOL_LINKAGE_NAME (struct minimal_symbol*) ; 
 scalar_t__ SYMBOL_VALUE (struct minimal_symbol*) ; 
 struct symtab_and_line find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 struct symtab* find_pc_sect_symtab (scalar_t__,struct bfd_section*) ; 
 int /*<<< orphan*/  init_sal (struct symtab_and_line*) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (scalar_t__) ; 
 struct minimal_symbol* lookup_minimal_symbol_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mst_solib_trampoline ; 

struct symtab_and_line
find_pc_sect_line (CORE_ADDR pc, struct bfd_section *section, int notcurrent)
{
  struct symtab *s;
  struct linetable *l;
  int len;
  int i;
  struct linetable_entry *item;
  struct symtab_and_line val;
  struct blockvector *bv;
  struct minimal_symbol *msymbol;
  struct minimal_symbol *mfunsym;

  /* Info on best line seen so far, and where it starts, and its file.  */

  struct linetable_entry *best = NULL;
  CORE_ADDR best_end = 0;
  struct symtab *best_symtab = 0;

  /* Store here the first line number
     of a file which contains the line at the smallest pc after PC.
     If we don't find a line whose range contains PC,
     we will use a line one less than this,
     with a range from the start of that file to the first line's pc.  */
  struct linetable_entry *alt = NULL;
  struct symtab *alt_symtab = 0;

  /* Info on best line seen in this file.  */

  struct linetable_entry *prev;

  /* If this pc is not from the current frame,
     it is the address of the end of a call instruction.
     Quite likely that is the start of the following statement.
     But what we want is the statement containing the instruction.
     Fudge the pc to make sure we get that.  */

  init_sal (&val);		/* initialize to zeroes */

  /* It's tempting to assume that, if we can't find debugging info for
     any function enclosing PC, that we shouldn't search for line
     number info, either.  However, GAS can emit line number info for
     assembly files --- very helpful when debugging hand-written
     assembly code.  In such a case, we'd have no debug info for the
     function, but we would have line info.  */

  if (notcurrent)
    pc -= 1;

  /* elz: added this because this function returned the wrong
     information if the pc belongs to a stub (import/export)
     to call a shlib function. This stub would be anywhere between
     two functions in the target, and the line info was erroneously 
     taken to be the one of the line before the pc. 
   */
  /* RT: Further explanation:

   * We have stubs (trampolines) inserted between procedures.
   *
   * Example: "shr1" exists in a shared library, and a "shr1" stub also
   * exists in the main image.
   *
   * In the minimal symbol table, we have a bunch of symbols
   * sorted by start address. The stubs are marked as "trampoline",
   * the others appear as text. E.g.:
   *
   *  Minimal symbol table for main image 
   *     main:  code for main (text symbol)
   *     shr1: stub  (trampoline symbol)
   *     foo:   code for foo (text symbol)
   *     ...
   *  Minimal symbol table for "shr1" image:
   *     ...
   *     shr1: code for shr1 (text symbol)
   *     ...
   *
   * So the code below is trying to detect if we are in the stub
   * ("shr1" stub), and if so, find the real code ("shr1" trampoline),
   * and if found,  do the symbolization from the real-code address
   * rather than the stub address.
   *
   * Assumptions being made about the minimal symbol table:
   *   1. lookup_minimal_symbol_by_pc() will return a trampoline only
   *      if we're really in the trampoline. If we're beyond it (say
   *      we're in "foo" in the above example), it'll have a closer 
   *      symbol (the "foo" text symbol for example) and will not
   *      return the trampoline.
   *   2. lookup_minimal_symbol_text() will find a real text symbol
   *      corresponding to the trampoline, and whose address will
   *      be different than the trampoline address. I put in a sanity
   *      check for the address being the same, to avoid an
   *      infinite recursion.
   */
  msymbol = lookup_minimal_symbol_by_pc (pc);
  if (msymbol != NULL)
    if (MSYMBOL_TYPE (msymbol) == mst_solib_trampoline)
      {
	mfunsym = lookup_minimal_symbol_text (SYMBOL_LINKAGE_NAME (msymbol),
					      NULL);
	if (mfunsym == NULL)
	  /* I eliminated this warning since it is coming out
	   * in the following situation:
	   * gdb shmain // test program with shared libraries
	   * (gdb) break shr1  // function in shared lib
	   * Warning: In stub for ...
	   * In the above situation, the shared lib is not loaded yet, 
	   * so of course we can't find the real func/line info,
	   * but the "break" still works, and the warning is annoying.
	   * So I commented out the warning. RT */
	  /* warning ("In stub for %s; unable to find real function/line info", SYMBOL_LINKAGE_NAME (msymbol)) */ ;
	/* fall through */
	else if (SYMBOL_VALUE (mfunsym) == SYMBOL_VALUE (msymbol))
	  /* Avoid infinite recursion */
	  /* See above comment about why warning is commented out */
	  /* warning ("In stub for %s; unable to find real function/line info", SYMBOL_LINKAGE_NAME (msymbol)) */ ;
	/* fall through */
	else
	  return find_pc_line (SYMBOL_VALUE (mfunsym), 0);
      }


  s = find_pc_sect_symtab (pc, section);
  if (!s)
    {
      /* if no symbol information, return previous pc */
      if (notcurrent)
	pc++;
      val.pc = pc;
      return val;
    }

  bv = BLOCKVECTOR (s);

  /* Look at all the symtabs that share this blockvector.
     They all have the same apriori range, that we found was right;
     but they have different line tables.  */

  for (; s && BLOCKVECTOR (s) == bv; s = s->next)
    {
      /* Find the best line in this symtab.  */
      l = LINETABLE (s);
      if (!l)
	continue;
      len = l->nitems;
      if (len <= 0)
	{
	  /* I think len can be zero if the symtab lacks line numbers
	     (e.g. gcc -g1).  (Either that or the LINETABLE is NULL;
	     I'm not sure which, and maybe it depends on the symbol
	     reader).  */
	  continue;
	}

      prev = NULL;
      item = l->item;		/* Get first line info */

      /* Is this file's first line closer than the first lines of other files?
         If so, record this file, and its first line, as best alternate.  */
      if (item->pc > pc && (!alt || item->pc < alt->pc))
	{
	  alt = item;
	  alt_symtab = s;
	}

      for (i = 0; i < len; i++, item++)
	{
	  /* Leave prev pointing to the linetable entry for the last line
	     that started at or before PC.  */
	  if (item->pc > pc)
	    break;

	  prev = item;
	}

      /* At this point, prev points at the line whose start addr is <= pc, and
         item points at the next line.  If we ran off the end of the linetable
         (pc >= start of the last line), then prev == item.  If pc < start of
         the first line, prev will not be set.  */

      /* Is this file's best line closer than the best in the other files?
         If so, record this file, and its best line, as best so far.  Don't
         save prev if it represents the end of a function (i.e. line number
         0) instead of a real line.  */

      if (prev && prev->line && (!best || prev->pc > best->pc))
	{
	  best = prev;
	  best_symtab = s;

	  /* Discard BEST_END if it's before the PC of the current BEST.  */
	  if (best_end <= best->pc)
	    best_end = 0;
	}

      /* If another line (denoted by ITEM) is in the linetable and its
         PC is after BEST's PC, but before the current BEST_END, then
	 use ITEM's PC as the new best_end.  */
      if (best && i < len && item->pc > best->pc
          && (best_end == 0 || best_end > item->pc))
	best_end = item->pc;
    }

  if (!best_symtab)
    {
      if (!alt_symtab)
	{			/* If we didn't find any line # info, just
				   return zeros.  */
	  val.pc = pc;
	}
      else
	{
	  val.symtab = alt_symtab;
	  val.line = alt->line - 1;

	  /* Don't return line 0, that means that we didn't find the line.  */
	  if (val.line == 0)
	    ++val.line;

	  val.pc = BLOCK_END (BLOCKVECTOR_BLOCK (bv, GLOBAL_BLOCK));
	  val.end = alt->pc;
	}
    }
  else if (best->line == 0)
    {
      /* If our best fit is in a range of PC's for which no line
	 number info is available (line number is zero) then we didn't
	 find any valid line information. */
      val.pc = pc;
    }
  else
    {
      val.symtab = best_symtab;
      val.line = best->line;
      val.pc = best->pc;
      if (best_end && (!alt || best_end < alt->pc))
	val.end = best_end;
      else if (alt)
	val.end = alt->pc;
      else
	val.end = BLOCK_END (BLOCKVECTOR_BLOCK (bv, GLOBAL_BLOCK));
    }
  val.section = section;
  return val;
}