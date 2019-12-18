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
struct jv_parser {scalar_t__ st; int last_ch_was_ws; scalar_t__ column; int /*<<< orphan*/  line; } ;
typedef  char* presult ;
typedef  char* pfunc ;
typedef  int /*<<< orphan*/  jv ;
typedef  int chclass ;

/* Variables and functions */
#define  INVALID 132 
 scalar_t__ JV_PARSER_NORMAL ; 
 scalar_t__ JV_PARSER_STRING ; 
 scalar_t__ JV_PARSER_STRING_ESCAPE ; 
#define  LITERAL 131 
 char* OK ; 
#define  QUOTE 130 
#define  STRUCTURE 129 
 int /*<<< orphan*/  TRY (scalar_t__) ; 
#define  WHITESPACE 128 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_done (struct jv_parser*,int /*<<< orphan*/ *) ; 
 scalar_t__ check_literal (struct jv_parser*) ; 
 scalar_t__ check_truncation (struct jv_parser*) ; 
 int classify (char) ; 
 scalar_t__ found_string (struct jv_parser*) ; 
 scalar_t__ is_top_num (struct jv_parser*) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid () ; 
 int /*<<< orphan*/  jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_reset (struct jv_parser*) ; 
 scalar_t__ token (struct jv_parser*,char) ; 
 int /*<<< orphan*/  tokenadd (struct jv_parser*,char) ; 

__attribute__((used)) static pfunc scan(struct jv_parser* p, char ch, jv* out) {
  p->column++;
  if (ch == '\n') {
    p->line++;
    p->column = 0;
  }
  if (ch == '\036' /* ASCII RS; see draft-ietf-json-sequence-07 */) {
    if (check_truncation(p)) {
      if (check_literal(p) == 0 && is_top_num(p))
        return "Potentially truncated top-level numeric value";
      return "Truncated value";
    }
    TRY(check_literal(p));
    if (p->st == JV_PARSER_NORMAL && check_done(p, out))
      return OK;
    // shouldn't happen?
    assert(!jv_is_valid(*out));
    parser_reset(p);
    jv_free(*out);
    *out = jv_invalid();
    return OK;
  }
  presult answer = 0;
  p->last_ch_was_ws = 0;
  if (p->st == JV_PARSER_NORMAL) {
    chclass cls = classify(ch);
    if (cls == WHITESPACE)
      p->last_ch_was_ws = 1;
    if (cls != LITERAL) {
      TRY(check_literal(p));
      if (check_done(p, out)) answer = OK;
    }
    switch (cls) {
    case LITERAL:
      tokenadd(p, ch);
      break;
    case WHITESPACE:
      break;
    case QUOTE:
      p->st = JV_PARSER_STRING;
      break;
    case STRUCTURE:
      TRY(token(p, ch));
      break;
    case INVALID:
      return "Invalid character";
    }
    if (check_done(p, out)) answer = OK;
  } else {
    if (ch == '"' && p->st == JV_PARSER_STRING) {
      TRY(found_string(p));
      p->st = JV_PARSER_NORMAL;
      if (check_done(p, out)) answer = OK;
    } else {
      tokenadd(p, ch);
      if (ch == '\\' && p->st == JV_PARSER_STRING) {
        p->st = JV_PARSER_STRING_ESCAPE;
      } else {
        p->st = JV_PARSER_STRING;
      }
    }
  }
  return answer;
}