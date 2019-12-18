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
struct jv_parser {int tokenpos; int* tokenbuf; int /*<<< orphan*/  dtoa; } ;
typedef  char* pfunc ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_INVALID ; 
 int /*<<< orphan*/  TRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_false () ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_null () ; 
 int /*<<< orphan*/  jv_number (double) ; 
 int /*<<< orphan*/  jv_number_with_literal (char const*) ; 
 int /*<<< orphan*/  jv_true () ; 
 double jvp_strtod (int /*<<< orphan*/ *,char const*,char**) ; 
 int /*<<< orphan*/  value (struct jv_parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pfunc check_literal(struct jv_parser* p) {
  if (p->tokenpos == 0) return 0;

  const char* pattern = 0;
  int plen;
  jv v;
  switch (p->tokenbuf[0]) {
  case 't': pattern = "true"; plen = 4; v = jv_true(); break;
  case 'f': pattern = "false"; plen = 5; v = jv_false(); break;
  case 'n': pattern = "null"; plen = 4; v = jv_null(); break;
  }
  if (pattern) {
    if (p->tokenpos != plen) return "Invalid literal";
    for (int i=0; i<plen; i++)
      if (p->tokenbuf[i] != pattern[i])
        return "Invalid literal";
    TRY(value(p, v));
  } else {
    // FIXME: better parser
    p->tokenbuf[p->tokenpos] = 0;
#ifdef USE_DECNUM
    jv number = jv_number_with_literal(p->tokenbuf);
    if (jv_get_kind(number) == JV_KIND_INVALID) {
      return "Invalid numeric literal";
    }
    TRY(value(p, number));
#else
    char *end = 0;
    double d = jvp_strtod(&p->dtoa, p->tokenbuf, &end);
    if (end == 0 || *end != 0) {
      return "Invalid numeric literal";
    }
    TRY(value(p, jv_number(d)));
#endif
  }
  p->tokenpos = 0;
  return 0;
}