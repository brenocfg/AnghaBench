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
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 
 char* jvp_utf8_next (char const*,char const*,int*) ; 
 int /*<<< orphan*/  put_buf (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_char (char,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_str (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 

__attribute__((used)) static void jvp_dump_string(jv str, int ascii_only, FILE* F, jv* S, int T) {
  assert(jv_get_kind(str) == JV_KIND_STRING);
  const char* i = jv_string_value(str);
  const char* end = i + jv_string_length_bytes(jv_copy(str));
  const char* cstart;
  int c = 0;
  char buf[32];
  put_char('"', F, S, T);
  while ((i = jvp_utf8_next((cstart = i), end, &c))) {
    assert(c != -1);
    int unicode_escape = 0;
    if (0x20 <= c && c <= 0x7E) {
      // printable ASCII
      if (c == '"' || c == '\\') {
        put_char('\\', F, S, T);
      }
      put_char(c, F, S, T);
    } else if (c < 0x20 || c == 0x7F) {
      // ASCII control character
      switch (c) {
      case '\b':
        put_char('\\', F, S, T);
        put_char('b', F, S, T);
        break;
      case '\t':
        put_char('\\', F, S, T);
        put_char('t', F, S, T);
        break;
      case '\r':
        put_char('\\', F, S, T);
        put_char('r', F, S, T);
        break;
      case '\n':
        put_char('\\', F, S, T);
        put_char('n', F, S, T);
        break;
      case '\f':
        put_char('\\', F, S, T);
        put_char('f', F, S, T);
        break;
      default:
        unicode_escape = 1;
        break;
      }
    } else {
      if (ascii_only) {
        unicode_escape = 1;
      } else {
        put_buf(cstart, i - cstart, F, S, T);
      }
    }
    if (unicode_escape) {
      if (c <= 0xffff) {
        snprintf(buf, sizeof(buf), "\\u%04x", c);
      } else {
        c -= 0x10000;
        snprintf(buf, sizeof(buf), "\\u%04x\\u%04x",
                0xD800 | ((c & 0xffc00) >> 10),
                0xDC00 | (c & 0x003ff));
      }
      put_str(buf, F, S, T);
    }
  }
  assert(c != -1);
  put_char('"', F, S, T);
}