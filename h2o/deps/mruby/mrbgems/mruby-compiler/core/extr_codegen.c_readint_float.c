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
typedef  int /*<<< orphan*/  codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  codegen_error (int /*<<< orphan*/ *,char*) ; 
 char* mrb_digitmap ; 
 int strlen (char const*) ; 
 char tolower (unsigned char) ; 

__attribute__((used)) static double
readint_float(codegen_scope *s, const char *p, int base)
{
  const char *e = p + strlen(p);
  double f = 0;
  int n;

  if (*p == '+') p++;
  while (p < e) {
    char c = *p;
    c = tolower((unsigned char)c);
    for (n=0; n<base; n++) {
      if (mrb_digitmap[n] == c) {
        f *= base;
        f += n;
        break;
      }
    }
    if (n == base) {
      codegen_error(s, "malformed readint input");
    }
    p++;
  }
  return f;
}