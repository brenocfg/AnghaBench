#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct connection {int /*<<< orphan*/  Tmp; int /*<<< orphan*/  In; } ;
struct TYPE_9__ {unsigned int member_0; int member_1; unsigned int member_2; unsigned int member_3; } ;
typedef  TYPE_1__ request_t ;
typedef  int /*<<< orphan*/  request ;
struct TYPE_10__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  uahash; int /*<<< orphan*/  ip; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ antispam_pattern_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT ; 
 int MAX_PATTERN_LEN ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  add_pattern ; 
 int do_add_pattern (TYPE_2__,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,int) ; 
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 
 int /*<<< orphan*/  init_tmp_buffers (struct connection*) ; 
 int mct_add ; 
 int /*<<< orphan*/  other ; 
 int /*<<< orphan*/  set_matches ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,int*,...) ; 
 int /*<<< orphan*/  st_printf (char*,unsigned int,int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  st_safe_read_in (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (TYPE_1__*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int const) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__* value_buf ; 
 int verbosity ; 
 int write_out (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

int memcache_store (struct connection *c, int op, const char *key, int key_len, int flags, int delay, int size) {
  INIT;

  free_tmp_buffers (c);
  if (verbosity >= 2) {
    fprintf (stderr, "memcache_store: key='%s', key_len=%d, value_len=%d\n", key, key_len, size);
  }

  if (unlikely (size >= MAX_PATTERN_LEN)) {
    RETURN (other, -2);
  }

  const int shift = 7;      // shift  == |pattern| == |matches|

  // set ("pattern{$id},{$ip},{$uahash}[,{$flags}]", $str);
  if (key_len >= shift && !strncmp (key, "pattern", shift)) {
    antispam_pattern_t p;
    int already_read = 0;
    st_safe_read_in (&c->In, value_buf, size);

    if (sscanf (key + shift, "%d,%u,%u%n,%hu%n", &p.id, &p.ip, &p.uahash, &already_read, &p.flags, &already_read) < 3
     || key[shift + already_read]) {
      RETURN (add_pattern, 0);
    }
    int res = do_add_pattern (p, strlen (value_buf), value_buf, (op != mct_add));
    RETURN (add_pattern, res);
  }
  // set ("matches{$ip},{$uahash},{$random_tag}", ${text});
  else if (key_len >= shift && !strncmp (key, "matches", shift)) {
    int already_read = 0;
    unsigned int ip, uahash, random_tag;

    st_safe_read_in (&c->In, value_buf, size);
    if (sscanf (key + shift, "%u,%u,%u%n", &ip, &uahash, &random_tag, &already_read) != 3 || key[shift + already_read]) {
      RETURN (set_matches, 0);
    }

    bool res = TRUE;
    request_t request = {random_tag, size, ip, uahash};
    init_tmp_buffers (c);
    if (verbosity >= 3) {
      st_printf ("STORED: random_tag = %u, size = %d, ip = %u, uahash = %u\n"
                   "expect '$2get matches$6%u$^' command\n", random_tag, size, ip, uahash, random_tag);
    }
    res &= (write_out (c->Tmp, &request, sizeof (request)) == sizeof (request));
    res &= (write_out (c->Tmp, value_buf, size) == size);
    RETURN (set_matches, res);
  }

  RETURN (other, -2);
}