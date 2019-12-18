#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  userpair_t ;
struct username_index {int dummy; } ;
typedef  scalar_t__ hash_t ;
struct TYPE_5__ {int user_id; scalar_t__ hash; int users; int* offset; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int Dc ; 
 int MAX_PAIRS ; 
 int MAX_USERS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 TYPE_1__* P ; 
 int Pc ; 
 TYPE_1__ U ; 
 int /*<<< orphan*/  USERNAME_HASH_INDEX_MAGIC ; 
 void* UU ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int getopt (int,char**,char*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  my_psort (int /*<<< orphan*/ ,int) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int optind ; 
 int /*<<< orphan*/  output_stats () ; 
 char* progname ; 
 int read (scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 int write (int,TYPE_1__*,int) ; 

int main (int argc, char *argv[]) {
  int i, r;
  hash_t p = 0;
  progname = argv[0];
  while ((i = getopt (argc, argv, "hv")) != -1) {
    switch (i) {
    case 'v':
      verbose = 1;
      break;
    case 'h':
      usage();
      return 2;
    }
  }
  if (argc <= optind) {
    usage();
    return 2;
  }

  P = malloc (MAX_PAIRS * sizeof (userpair_t));
  UU = malloc (sizeof (struct username_index));
  assert (P && UU);

  while (optind < argc) {
    fd = open (argv[optind], O_RDONLY);
    if (fd < 0) {
      fprintf (stderr, "%s: cannot open() %s: %m\n", progname, argv[optind]);
      optind++;
      continue;
    }
    r = (MAX_PAIRS - Pc) * sizeof(userpair_t);
    i = read (fd, P + Pc, r);
    if (i < 0) {
      fprintf (stderr, "%s: error reading %s: %m\n", progname, argv[optind]);
      return 1;
    }
    if (i == r) {
      fprintf (stderr, "%s: error reading %s: hash space exhausted (%ld entries)\n", progname, argv[optind], MAX_PAIRS);
      return 1;
    }
    Pc += i / sizeof(userpair_t);    
    close (fd);
    optind++;
  }

  my_psort(0, Pc-1);

  for (i = 0; i < Pc; i++) {
    int j = P[i].user_id;
    hash_t h = P[i].hash;
    assert (j < MAX_USERS-3);
    while (U.users <= j) {
      U.offset[U.users++] = Dc;
      p = 0;
    }
    if (h != p) {
      ((hash_t *) P)[Dc++] = h;
      p = h;
    }
  }
  U.offset[U.users++] = Dc;
  if (U.users & 1) { U.offset[U.users++] = Dc; }

  U.magic = USERNAME_HASH_INDEX_MAGIC;
  r = 8 + 4 * U.users;
  assert (write (1, &U, r) == r);
  r = Dc * 8;
  assert (write (1, P, r) == r);

  if (verbose) {
    output_stats();
  }
                                      
  return 0;
}