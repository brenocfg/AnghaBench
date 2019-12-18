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
 int /*<<< orphan*/  ADD_PMALLOC (int /*<<< orphan*/ ) ; 
 long long MAX_TL_CONFIG_SIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_rpc_parse (char*,long long) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,long long) ; 
 int /*<<< orphan*/  free (char*) ; 
 long long lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* malloc (long long) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 long long read (int,char*,long long) ; 
 int renew_tl_config () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_config_name ; 
 int verbosity ; 
 int /*<<< orphan*/  zzstrdup (char const*) ; 

int read_tl_config (const char *name) {
  int fd = open (name, O_RDONLY);
//  fprintf (stderr, "fd = %d\n", fd);
  if (fd < 0) { return -1; }
  long long x = lseek (fd, 0, SEEK_END);
  if (x < 0) { return -1; }
  if (x > MAX_TL_CONFIG_SIZE) {
    return -1;
  }
  if (verbosity >= 2) {
    fprintf (stderr, "File found. Name %s. size = %lld\n", name, x);
  }
  char *s = malloc (x);
  assert (lseek (fd, 0, SEEK_SET) == 0);
  assert (read (fd, s, x) == x);
  close (fd);
  do_rpc_parse (s, x);
  int res = renew_tl_config ();
  free (s);
  if (res > 0) {
    tl_config_name = zzstrdup (name);
    ADD_PMALLOC (strlen (tl_config_name));
  }

  return res;
}