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
typedef  int pcre_uint32 ;
typedef  int pcre_uchar ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ PRINTABLE (int) ; 
 int* PRIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  utf8_table3 ; 
 int /*<<< orphan*/  utf8_table4 ; 

__attribute__((used)) static unsigned int
print_char(FILE *f, pcre_uchar *ptr, BOOL utf)
{
pcre_uint32 c = *ptr;

#ifndef SUPPORT_UTF

(void)utf;  /* Avoid compiler warning */
if (PRINTABLE(c)) fprintf(f, "%c", (char)c);
else if (c <= 0x80) fprintf(f, "\\x%02x", c);
else fprintf(f, "\\x{%x}", c);
return 0;

#else

#if defined COMPILE_PCRE8

if (!utf || (c & 0xc0) != 0xc0)
  {
  if (PRINTABLE(c)) fprintf(f, "%c", (char)c);
  else if (c < 0x80) fprintf(f, "\\x%02x", c);
  else fprintf(f, "\\x{%02x}", c);
  return 0;
  }
else
  {
  int i;
  int a = PRIV(utf8_table4)[c & 0x3f];  /* Number of additional bytes */
  int s = 6*a;
  c = (c & PRIV(utf8_table3)[a]) << s;
  for (i = 1; i <= a; i++)
    {
    /* This is a check for malformed UTF-8; it should only occur if the sanity
    check has been turned off. Rather than swallow random bytes, just stop if
    we hit a bad one. Print it with \X instead of \x as an indication. */

    if ((ptr[i] & 0xc0) != 0x80)
      {
      fprintf(f, "\\X{%x}", c);
      return i - 1;
      }

    /* The byte is OK */

    s -= 6;
    c |= (ptr[i] & 0x3f) << s;
    }
  fprintf(f, "\\x{%x}", c);
  return a;
  }

#elif defined COMPILE_PCRE16

if (!utf || (c & 0xfc00) != 0xd800)
  {
  if (PRINTABLE(c)) fprintf(f, "%c", (char)c);
  else if (c <= 0x80) fprintf(f, "\\x%02x", c);
  else fprintf(f, "\\x{%02x}", c);
  return 0;
  }
else
  {
  /* This is a check for malformed UTF-16; it should only occur if the sanity
  check has been turned off. Rather than swallow a low surrogate, just stop if
  we hit a bad one. Print it with \X instead of \x as an indication. */

  if ((ptr[1] & 0xfc00) != 0xdc00)
    {
    fprintf(f, "\\X{%x}", c);
    return 0;
    }

  c = (((c & 0x3ff) << 10) | (ptr[1] & 0x3ff)) + 0x10000;
  fprintf(f, "\\x{%x}", c);
  return 1;
  }

#elif defined COMPILE_PCRE32

if (!utf || (c & 0xfffff800u) != 0xd800u)
  {
  if (PRINTABLE(c)) fprintf(f, "%c", (char)c);
  else if (c <= 0x80) fprintf(f, "\\x%02x", c);
  else fprintf(f, "\\x{%x}", c);
  return 0;
  }
else
  {
  /* This is a check for malformed UTF-32; it should only occur if the sanity
  check has been turned off. Rather than swallow a surrogate, just stop if
  we hit one. Print it with \X instead of \x as an indication. */
  fprintf(f, "\\X{%x}", c);
  return 0;
  }

#endif /* COMPILE_PCRE[8|16|32] */

#endif /* SUPPORT_UTF */
}