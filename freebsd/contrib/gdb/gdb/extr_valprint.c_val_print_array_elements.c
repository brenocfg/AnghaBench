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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 unsigned int TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  annotate_array_section_begin (unsigned int,struct type*) ; 
 int /*<<< orphan*/  annotate_array_section_end () ; 
 int /*<<< orphan*/  annotate_elt () ; 
 int /*<<< orphan*/  annotate_elt_rep (unsigned int) ; 
 int /*<<< orphan*/  annotate_elt_rep_end () ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  memcmp (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  n_spaces (int) ; 
 scalar_t__ prettyprint_arrays ; 
 unsigned int print_max ; 
 int /*<<< orphan*/  print_spaces_filtered (int,struct ui_file*) ; 
 unsigned int repeat_count_threshold ; 
 int /*<<< orphan*/  val_print (struct type*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ui_file*,int,int,int,int) ; 
 int /*<<< orphan*/  wrap_here (int /*<<< orphan*/ ) ; 

void
val_print_array_elements (struct type *type, char *valaddr, CORE_ADDR address,
			  struct ui_file *stream, int format, int deref_ref,
			  int recurse, enum val_prettyprint pretty,
			  unsigned int i)
{
  unsigned int things_printed = 0;
  unsigned len;
  struct type *elttype;
  unsigned eltlen;
  /* Position of the array element we are examining to see
     whether it is repeated.  */
  unsigned int rep1;
  /* Number of repetitions we have detected so far.  */
  unsigned int reps;

  elttype = TYPE_TARGET_TYPE (type);
  eltlen = TYPE_LENGTH (check_typedef (elttype));
  len = TYPE_LENGTH (type) / eltlen;

  annotate_array_section_begin (i, elttype);

  for (; i < len && things_printed < print_max; i++)
    {
      if (i != 0)
	{
	  if (prettyprint_arrays)
	    {
	      fprintf_filtered (stream, ",\n");
	      print_spaces_filtered (2 + 2 * recurse, stream);
	    }
	  else
	    {
	      fprintf_filtered (stream, ", ");
	    }
	}
      wrap_here (n_spaces (2 + 2 * recurse));

      rep1 = i + 1;
      reps = 1;
      while ((rep1 < len) &&
	     !memcmp (valaddr + i * eltlen, valaddr + rep1 * eltlen, eltlen))
	{
	  ++reps;
	  ++rep1;
	}

      if (reps > repeat_count_threshold)
	{
	  val_print (elttype, valaddr + i * eltlen, 0, 0, stream, format,
		     deref_ref, recurse + 1, pretty);
	  annotate_elt_rep (reps);
	  fprintf_filtered (stream, " <repeats %u times>", reps);
	  annotate_elt_rep_end ();

	  i = rep1 - 1;
	  things_printed += repeat_count_threshold;
	}
      else
	{
	  val_print (elttype, valaddr + i * eltlen, 0, 0, stream, format,
		     deref_ref, recurse + 1, pretty);
	  annotate_elt ();
	  things_printed++;
	}
    }
  annotate_array_section_end ();
  if (i < len)
    {
      fprintf_filtered (stream, "...");
    }
}