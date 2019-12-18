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

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 int BITS_IN_BYTES ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,int) ; 
 int /*<<< orphan*/  fputs_filtered (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  local_binary_format_prefix () ; 
 int /*<<< orphan*/  local_binary_format_suffix () ; 

void
print_binary_chars (struct ui_file *stream, unsigned char *valaddr,
		    unsigned len)
{

#define BITS_IN_BYTES 8

  unsigned char *p;
  unsigned int i;
  int b;

  /* Declared "int" so it will be signed.
   * This ensures that right shift will shift in zeros.
   */
  const int mask = 0x080;

  /* FIXME: We should be not printing leading zeroes in most cases.  */

  fputs_filtered (local_binary_format_prefix (), stream);
  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
    {
      for (p = valaddr;
	   p < valaddr + len;
	   p++)
	{
	  /* Every byte has 8 binary characters; peel off
	   * and print from the MSB end.
	   */
	  for (i = 0; i < (BITS_IN_BYTES * sizeof (*p)); i++)
	    {
	      if (*p & (mask >> i))
		b = 1;
	      else
		b = 0;

	      fprintf_filtered (stream, "%1d", b);
	    }
	}
    }
  else
    {
      for (p = valaddr + len - 1;
	   p >= valaddr;
	   p--)
	{
	  for (i = 0; i < (BITS_IN_BYTES * sizeof (*p)); i++)
	    {
	      if (*p & (mask >> i))
		b = 1;
	      else
		b = 0;

	      fprintf_filtered (stream, "%1d", b);
	    }
	}
    }
  fputs_filtered (local_binary_format_suffix (), stream);
}