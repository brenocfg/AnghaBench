#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reg_syntax_t ;
typedef  int /*<<< orphan*/  reg_errcode_t ;
struct TYPE_11__ {int /*<<< orphan*/  c; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_2__ opr; } ;
typedef  TYPE_3__ re_token_t ;
typedef  int /*<<< orphan*/  re_string_t ;
typedef  int /*<<< orphan*/  re_dfa_t ;
struct TYPE_10__ {int /*<<< orphan*/  ch; int /*<<< orphan*/  wch; } ;
struct TYPE_13__ {TYPE_1__ opr; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ bracket_elem_t ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_CHAR ; 
 scalar_t__ OP_CHARSET_RANGE ; 
 scalar_t__ OP_CLOSE_BRACKET ; 
 scalar_t__ OP_OPEN_CHAR_CLASS ; 
 scalar_t__ OP_OPEN_COLL_ELEM ; 
 scalar_t__ OP_OPEN_EQUIV_CLASS ; 
 int /*<<< orphan*/  REG_ERANGE ; 
 int /*<<< orphan*/  REG_NOERROR ; 
 int /*<<< orphan*/  SB_CHAR ; 
 int /*<<< orphan*/  parse_bracket_symbol (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  peek_token_bracket (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int re_string_char_size_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  re_string_cur_idx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  re_string_skip_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  re_string_wchar_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static reg_errcode_t
parse_bracket_element (bracket_elem_t *elem, re_string_t *regexp,
		       re_token_t *token, int token_len, re_dfa_t *dfa,
		       reg_syntax_t syntax, int accept_hyphen)
{
#ifdef RE_ENABLE_I18N
  int cur_char_size;
  cur_char_size = re_string_char_size_at (regexp, re_string_cur_idx (regexp));
  if (cur_char_size > 1)
    {
      elem->type = MB_CHAR;
      elem->opr.wch = re_string_wchar_at (regexp, re_string_cur_idx (regexp));
      re_string_skip_bytes (regexp, cur_char_size);
      return REG_NOERROR;
    }
#endif /* RE_ENABLE_I18N */
  re_string_skip_bytes (regexp, token_len); /* Skip a token.  */
  if (token->type == OP_OPEN_COLL_ELEM || token->type == OP_OPEN_CHAR_CLASS
      || token->type == OP_OPEN_EQUIV_CLASS)
    return parse_bracket_symbol (elem, regexp, token);
  if (BE (token->type == OP_CHARSET_RANGE, 0) && !accept_hyphen)
    {
      /* A '-' must only appear as anything but a range indicator before
	 the closing bracket.  Everything else is an error.  */
      re_token_t token2;
      (void) peek_token_bracket (&token2, regexp, syntax);
      if (token2.type != OP_CLOSE_BRACKET)
	/* The actual error value is not standardized since this whole
	   case is undefined.  But ERANGE makes good sense.  */
	return REG_ERANGE;
    }
  elem->type = SB_CHAR;
  elem->opr.ch = token->opr.c;
  return REG_NOERROR;
}