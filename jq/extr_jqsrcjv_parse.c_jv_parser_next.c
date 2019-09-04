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
struct jv_parser {int eof; char* curr_buf; int bom_strip_position; int flags; scalar_t__ st; scalar_t__ curr_buf_pos; scalar_t__ curr_buf_length; scalar_t__ stacklen; scalar_t__ stackpos; scalar_t__ column; int /*<<< orphan*/  line; int /*<<< orphan*/  last_ch_was_ws; int /*<<< orphan*/  next; int /*<<< orphan*/  path; scalar_t__ curr_buf_is_partial; } ;
typedef  scalar_t__ presult ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  JV_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ JV_PARSER_NORMAL ; 
 scalar_t__ JV_PARSER_WAITING_FOR_RS ; 
 int JV_PARSE_SEQ ; 
 int JV_PARSE_STREAMING ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_literal (struct jv_parser*) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid () ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  make_error (struct jv_parser*,char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  parser_reset (struct jv_parser*) ; 
 scalar_t__ scan (struct jv_parser*,char,int /*<<< orphan*/ *) ; 
 scalar_t__ stream_check_done (struct jv_parser*,int /*<<< orphan*/ *) ; 

jv jv_parser_next(struct jv_parser* p) {
  if (p->eof)
    return jv_invalid();
  if (!p->curr_buf)
    return jv_invalid(); // Need a buffer
  if (p->bom_strip_position == 0xff) {
    if (!(p->flags & JV_PARSE_SEQ))
      return jv_invalid_with_msg(jv_string("Malformed BOM"));
    p->st =JV_PARSER_WAITING_FOR_RS;
    parser_reset(p);
  }
  jv value = jv_invalid();
  if ((p->flags & JV_PARSE_STREAMING) && stream_check_done(p, &value))
    return value;
  char ch;
  presult msg = 0;
  while (!msg && p->curr_buf_pos < p->curr_buf_length) {
    ch = p->curr_buf[p->curr_buf_pos++];
    if (p->st == JV_PARSER_WAITING_FOR_RS) {
      if (ch == '\n') {
        p->line++;
        p->column = 0;
      } else {
        p->column++;
      }
      if (ch == '\036')
        p->st = JV_PARSER_NORMAL;
      continue; // need to resync, wait for RS
    }
    msg = scan(p, ch, &value);
  }
  if (msg == OK) {
    return value;
  } else if (msg) {
    jv_free(value);
    if (ch != '\036' && (p->flags & JV_PARSE_SEQ)) {
      // Skip to the next RS
      p->st = JV_PARSER_WAITING_FOR_RS;
      value = make_error(p, "%s at line %d, column %d (need RS to resync)", msg, p->line, p->column);
      parser_reset(p);
      return value;
    }
    value = make_error(p, "%s at line %d, column %d", msg, p->line, p->column);
    parser_reset(p);
    if (!(p->flags & JV_PARSE_SEQ)) {
      // We're not parsing a JSON text sequence; throw this buffer away.
      // XXX We should fail permanently here.
      p->curr_buf = 0;
      p->curr_buf_pos = 0;
    } // Else ch must be RS; don't clear buf so we can start parsing again after this ch
    return value;
  } else if (p->curr_buf_is_partial) {
    assert(p->curr_buf_pos == p->curr_buf_length);
    // need another buffer
    return jv_invalid();
  } else {
    // at EOF
    p->eof = 1;
    assert(p->curr_buf_pos == p->curr_buf_length);
    jv_free(value);
    if (p->st == JV_PARSER_WAITING_FOR_RS)
      return make_error(p, "Unfinished abandoned text at EOF at line %d, column %d", p->line, p->column);
    if (p->st != JV_PARSER_NORMAL) {
      value = make_error(p, "Unfinished string at EOF at line %d, column %d", p->line, p->column);
      parser_reset(p);
      p->st = JV_PARSER_WAITING_FOR_RS;
      return value;
    }
    if ((msg = check_literal(p))) {
      value = make_error(p, "%s at EOF at line %d, column %d", msg, p->line, p->column);
      parser_reset(p);
      p->st = JV_PARSER_WAITING_FOR_RS;
      return value;
    }
    if (((p->flags & JV_PARSE_STREAMING) && p->stacklen != 0) ||
        (!(p->flags & JV_PARSE_STREAMING) && p->stackpos != 0)) {
      value = make_error(p, "Unfinished JSON term at EOF at line %d, column %d", p->line, p->column);
      parser_reset(p);
      p->st = JV_PARSER_WAITING_FOR_RS;
      return value;
    }
    // p->next is either invalid (nothing here, but no syntax error)
    // or valid (this is the value). either way it's the thing to return
    if ((p->flags & JV_PARSE_STREAMING) && jv_is_valid(p->next)) {
      value = JV_ARRAY(jv_copy(p->path), p->next); // except in streaming mode we've got to make it [path,value]
    } else {
      value = p->next;
    }
    p->next = jv_invalid();
    if ((p->flags & JV_PARSE_SEQ) && !p->last_ch_was_ws && jv_get_kind(value) == JV_KIND_NUMBER) {
      jv_free(value);
      return make_error(p, "Potentially truncated top-level numeric value at EOF at line %d, column %d", p->line, p->column);
    }
    return value;
  }
}