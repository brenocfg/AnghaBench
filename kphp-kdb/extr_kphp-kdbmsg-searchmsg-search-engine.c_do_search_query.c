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
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int MAX_NET_RES ; 
 int /*<<< orphan*/  MAX_QUERY_WORDS ; 
 int /*<<< orphan*/  MaxQw ; 
 int Qw ; 
 int* Res ; 
 int ResL ; 
 int /*<<< orphan*/  UH ; 
 int /*<<< orphan*/  advance_write_ptr (int /*<<< orphan*/ *,int) ; 
 scalar_t__ do_combined_search () ; 
 int /*<<< orphan*/  dyn_user_header (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,char*) ; 
 char* get_write_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  load_user (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int now ; 
 int /*<<< orphan*/  process_text (char*) ; 
 int return_key_value (struct connection*,char*,char*,int) ; 
 size_t sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int strtol (char*,char**,int) ; 
 int tot_response_bytes ; 
 int tot_response_words ; 
 scalar_t__ verbosity ; 

int do_search_query (struct connection *c, char *key, int len) {
  int user_id, max_res, i, w;
  char *ptr, *s, *size_ptr;

  if (strncmp (key, "search(", 7)) { return -1; }
  s = key + 7;
  user_id = strtol (s, &ptr, 10);
  if (ptr == s || *ptr != ',' || user_id <= 0 || user_id > (1L<<30)) { 
    return -1; 
  }
  s = ptr+1;
  max_res = strtol (s, &ptr, 10);
  if (ptr == s || *ptr != ',' || max_res <= 0 || max_res > MAX_NET_RES) {
    return -1;
  }

  MaxQw = MAX_QUERY_WORDS;
  process_text(ptr+1);

  if (verbosity) {
    fprintf (stderr, "%d search query: uid=%d, max_res=%d, keywords=%d, text='%s'\n", now, user_id, max_res, Qw, ptr+1);
  }

  UH = dyn_user_header(user_id,0);
  if (!load_user(user_id) && !UH) {
    return return_key_value (c, key, "no_user", 7);
  }

  if (!Qw) {
    return return_key_value (c, key, "empty_query", 11);
  }

  if (do_combined_search() < 0) {
    return return_key_value (c, key, "search_error", 12);
  }

  ptr = get_write_ptr (&c->Out, 512);
  if (!ptr) return -1;
  s = ptr + 480;
  memcpy (ptr, "VALUE ", 6);
  ptr += 6;
  memcpy (ptr, key, len);
  ptr += len;
  memcpy (ptr, " 0 .........\r\n", 14);
  size_ptr = ptr + 3;
  ptr += 14;
  ptr += w = sprintf (ptr, "%d", ResL);
  for (i = 0; i < ResL && i < max_res; i++) {
    int t;
    if (ptr >= s) {
      advance_write_ptr (&c->Out, ptr - (s - 480));
      ptr = get_write_ptr (&c->Out, 512);
      if (!ptr) return -1;
      s = ptr + 480;
    }
    *ptr++ = ',';  w++;
    w += t = sprintf (ptr, "%d", Res[i]);
    ptr += t;
  }
  size_ptr[sprintf (size_ptr, "% 9d", w)] = '\r';
  memcpy (ptr, "\r\nEND\r\n", 7);
  ptr += 7;
  advance_write_ptr (&c->Out, ptr - (s - 480));

  tot_response_words += ResL;
  tot_response_bytes += w;

  return 0;
}