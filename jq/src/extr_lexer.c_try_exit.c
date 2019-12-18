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
typedef  int /*<<< orphan*/  yyscan_t ;

/* Variables and functions */
 int INVALID_CHARACTER ; 
#define  IN_BRACE 131 
#define  IN_BRACKET 130 
#define  IN_PAREN 129 
#define  IN_QQINTERP 128 
 int QQSTRING_INTERP_END ; 
 int /*<<< orphan*/  assert (char) ; 
 int /*<<< orphan*/  yy_pop_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_exit(int c, int state, yyscan_t yyscanner) {
  char match = 0;
  int ret;
  switch (state) {
  case IN_PAREN: match = ret = ')'; break;
  case IN_BRACKET: match = ret = ']'; break;
  case IN_BRACE: match = ret = '}'; break;

  case IN_QQINTERP:
    match = ')';
    ret = QQSTRING_INTERP_END;
    break;

  default:
    // may not be the best error to give
    return INVALID_CHARACTER;
  }
  assert(match);
  if (match == c) {
    yy_pop_state(yyscanner);
    return ret;
  } else {
    // FIXME: should we pop? Give a better error at least
    return INVALID_CHARACTER;
  }
}