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
struct symtab {int language; } ;
typedef  enum language { ____Placeholder_language } language ;

/* Variables and functions */
 scalar_t__ deprecated_selected_frame ; 
 struct symtab* find_pc_symtab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_address_in_block (scalar_t__) ; 
 int language_unknown ; 

enum language
get_frame_language (void)
{
  struct symtab *s;
  enum language flang;		/* The language of the current frame */

  if (deprecated_selected_frame)
    {
      /* We determine the current frame language by looking up its
         associated symtab.  To retrieve this symtab, we use the frame PC.
         However we cannot use the frame pc as is, because it usually points
         to the instruction following the "call", which is sometimes the first
         instruction of another function.  So we rely on
         get_frame_address_in_block(), it provides us with a PC which is
         guaranteed to be inside the frame's code block.  */
      s = find_pc_symtab (get_frame_address_in_block (deprecated_selected_frame));
      if (s)
	flang = s->language;
      else
	flang = language_unknown;
    }
  else
    flang = language_unknown;

  return flang;
}