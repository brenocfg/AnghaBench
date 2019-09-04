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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int* dumps ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

void load_dump (int t) {
  assert (0 < t && t < 256);
  assert (dumps[t]);

  if (verbosity > 1) {
    fprintf (stderr, "Begin of loading dump %d\n", t);
  }

//not supported now
/*
  size_t len, read_len;

  sprintf (file_name, "dump.%d", t);
  dl_open_file (4, file_name, 0);

  char c = '0';
  int usn = 0, i;
  do {
    usn = usn * 10 + c - '0';
    len = sizeof (char);
    read_len = read (fd[4], &c, len);
    assert (read_len == len);
  } while ('0' <= c && c <= '9');

  if (verbosity) {
    fprintf (stderr, "usn = %d\n", usn);
  }

  len = sizeof (user) * usn;

  vector (user, users);
  vector_init (users);

  read_len = read (fd[4], vector_zpb (users, usn), len);
  assert (read_len == len);

  int scn = 0;
  for (i = 0; i < users_size; i++) {
    scn += users[i].len;
  }

  if (verbosity) {
    fprintf (stderr, "scn = %d\n", scn);
  }

  len = sizeof (score) * scn;
  vector_init (scores);
  read_len = read (fd[4], vector_zpb (scores, scn), len);
  assert (read_len == len);

  int ns = 0, lu = 0, j, ls = 0;
  for (i = 0; i < users_size; i++) {
    int sn = users[i].len, os = ns;

    for (j = 0; j < sn; j++, ls++) {
      if (map_int_int_get (&fid_id, scores[ls].fid) != NULL) {
        scores[ns++] = scores[ls];
      }
    }

    if (ns - os > 0) {
      users[lu].len = ns - os;
      users[lu++].id = users[i].id;
    } else {
      ns = os;
    }
  }
  vector_resize (scores, ns);
  vector_resize (users, lu);

  scn = 0;
  for (i = 0; i < users_size; i++) {
    user *u = conv_uid (users[i].id);
    assert (u != NULL);
    u->objs = scores + scn;
    u->objs_n = users[i].len;

    scn += users[i].len;

    assert (u->objs_n <= MAX_FIDS);
  }

  vector_free (users);

  dl_close_file (4);
*/
  if (verbosity > 1) {
    fprintf (stderr, "End of loading dump %d\n", t);
  }
}