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
 scalar_t__ TARGET_BYTE_ORDER ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,unsigned char) ; 
 int /*<<< orphan*/  fputs_filtered (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  local_hex_format_prefix () ; 
 int /*<<< orphan*/  local_hex_format_suffix () ; 

void
print_hex_chars (struct ui_file *stream, unsigned char *valaddr, unsigned len)
{
  unsigned char *p;

  /* FIXME: We should be not printing leading zeroes in most cases.  */

  fputs_filtered (local_hex_format_prefix (), stream);
  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
    {
      for (p = valaddr;
	   p < valaddr + len;
	   p++)
	{
	  fprintf_filtered (stream, "%02x", *p);
	}
    }
  else
    {
      for (p = valaddr + len - 1;
	   p >= valaddr;
	   p--)
	{
	  fprintf_filtered (stream, "%02x", *p);
	}
    }
  fputs_filtered (local_hex_format_suffix (), stream);
}