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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int TYPE_LENGTH (struct type*) ; 
 scalar_t__ TYPE_UNSIGNED (struct type*) ; 
 scalar_t__ extract_long_unsigned_integer (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_hex_chars (struct ui_file*,unsigned char*,int) ; 
 int /*<<< orphan*/  print_longest (struct ui_file*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_long (struct type*,char*) ; 

void
val_print_type_code_int (struct type *type, char *valaddr,
			 struct ui_file *stream)
{
  if (TYPE_LENGTH (type) > sizeof (LONGEST))
    {
      LONGEST val;

      if (TYPE_UNSIGNED (type)
	  && extract_long_unsigned_integer (valaddr, TYPE_LENGTH (type),
					    &val))
	{
	  print_longest (stream, 'u', 0, val);
	}
      else
	{
	  /* Signed, or we couldn't turn an unsigned value into a
	     LONGEST.  For signed values, one could assume two's
	     complement (a reasonable assumption, I think) and do
	     better than this.  */
	  print_hex_chars (stream, (unsigned char *) valaddr,
			   TYPE_LENGTH (type));
	}
    }
  else
    {
      print_longest (stream, TYPE_UNSIGNED (type) ? 'u' : 'd', 0,
		     unpack_long (type, valaddr));
    }
}