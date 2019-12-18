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
struct floatformat {int dummy; } ;
typedef  double DOUBLEST ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 unsigned int TYPE_LENGTH (struct type*) ; 
 struct floatformat* floatformat_from_type (struct type*) ; 
 scalar_t__ floatformat_is_nan (struct floatformat const*,char*) ; 
 scalar_t__ floatformat_is_negative (struct floatformat const*,char*) ; 
 int /*<<< orphan*/  floatformat_mantissa (struct floatformat const*,char*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  local_hex_format_prefix () ; 
 int /*<<< orphan*/  local_hex_format_suffix () ; 
 double unpack_double (struct type*,char*,int*) ; 

void
print_floating (char *valaddr, struct type *type, struct ui_file *stream)
{
  DOUBLEST doub;
  int inv;
  const struct floatformat *fmt = NULL;
  unsigned len = TYPE_LENGTH (type);

  /* If it is a floating-point, check for obvious problems.  */
  if (TYPE_CODE (type) == TYPE_CODE_FLT)
    fmt = floatformat_from_type (type);
  if (fmt != NULL && floatformat_is_nan (fmt, valaddr))
    {
      if (floatformat_is_negative (fmt, valaddr))
	fprintf_filtered (stream, "-");
      fprintf_filtered (stream, "nan(");
      fputs_filtered (local_hex_format_prefix (), stream);
      fputs_filtered (floatformat_mantissa (fmt, valaddr), stream);
      fputs_filtered (local_hex_format_suffix (), stream);
      fprintf_filtered (stream, ")");
      return;
    }

  /* NOTE: cagney/2002-01-15: The TYPE passed into print_floating()
     isn't necessarily a TYPE_CODE_FLT.  Consequently, unpack_double
     needs to be used as that takes care of any necessary type
     conversions.  Such conversions are of course direct to DOUBLEST
     and disregard any possible target floating point limitations.
     For instance, a u64 would be converted and displayed exactly on a
     host with 80 bit DOUBLEST but with loss of information on a host
     with 64 bit DOUBLEST.  */

  doub = unpack_double (type, valaddr, &inv);
  if (inv)
    {
      fprintf_filtered (stream, "<invalid float value>");
      return;
    }

  /* FIXME: kettenis/2001-01-20: The following code makes too much
     assumptions about the host and target floating point format.  */

  /* NOTE: cagney/2002-02-03: Since the TYPE of what was passed in may
     not necessarially be a TYPE_CODE_FLT, the below ignores that and
     instead uses the type's length to determine the precision of the
     floating-point value being printed.  */

  if (len < sizeof (double))
      fprintf_filtered (stream, "%.9g", (double) doub);
  else if (len == sizeof (double))
      fprintf_filtered (stream, "%.17g", (double) doub);
  else
#ifdef PRINTF_HAS_LONG_DOUBLE
    fprintf_filtered (stream, "%.35Lg", doub);
#else
    /* This at least wins with values that are representable as
       doubles.  */
    fprintf_filtered (stream, "%.17g", (double) doub);
#endif
}