#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vector ;
struct TYPE_4__ {int n; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int A ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (void*) ; 
 scalar_t__ change_user (char*) ; 
 int engineN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fd ; 
 int /*<<< orphan*/  flush_w_buff () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * friends_list ; 
 scalar_t__ friends_list_n ; 
 int* fsize ; 
 int /*<<< orphan*/  gen_events (int /*<<< orphan*/ *,scalar_t__) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_data () ; 
 int /*<<< orphan*/  init_files (int) ; 
 void* input_name ; 
 long long* l_len ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int max_user_events ; 
 int /*<<< orphan*/  my_read () ; 
 int /*<<< orphan*/  my_write (int /*<<< orphan*/ ,int) ; 
 void* optarg ; 
 int optind ; 
 void* output_name ; 
 char* progname ; 
 TYPE_1__* qmalloc (int) ; 
 long long* qmalloc0 (int) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int uf ; 
 int /*<<< orphan*/  usage () ; 
 int userN ; 
 char* username ; 
 TYPE_1__* v ; 
 int /*<<< orphan*/  vct_init (TYPE_1__*) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,long long*,int) ; 

int main (int argc, char *argv[]) {
  int i;

  set_debug_handlers();
  progname = argv[0];
  srand (time (NULL));

  if (argc == 1) {
    usage();
    return 2;
  }

  while ((i = getopt (argc, argv, "i:o:hvU:E:u:T:m:")) != -1) {
    switch (i) {
    case 'v':
      verbosity++;
      break;
    case 'h':
      usage();
      return 2;
    case 'i':
      input_name = optarg;
      break;
    case 'o':
      output_name = optarg;
      break;
    case 'U':
      userN = atoi (optarg);
      break;
    case 'E':
      engineN = atoi (optarg);
      break;
    case 'T':
      assert (uf == -1);
      uf = atoi (optarg);
      break;
    case 'u':
      username = optarg;
      break;
    case 'm':
      max_user_events = atoi (optarg);
      assert (1 <= max_user_events && max_user_events <= 10000000);
      break;
    }
  }

  assert (uf >= 0);

  if (argc != optind) {
    usage();
    return 2;
  }

  if (verbosity) {
    fprintf (stderr, "userN = %d, engineN = %d\n", userN, engineN);
  }

  if (change_user (username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  assert (0 < engineN);

  init_files (2);

  init_data();

  int cnt = userN / engineN;
  v = qmalloc (sizeof (vector) * (cnt + 2));

  for (i = 0; i <= cnt; i++) {
    vct_init (&v[i]);
  }

  assert (fsize[0] % 8 == 0);

  long long total = fsize[0] / 8;

  assert (total > 0);

  int prev = -1;
  while (total--) {
    my_read();
    if (A != prev) {
      prev = A;
      gen_events (friends_list, friends_list_n);
      friends_list_n = 0;
    }

    friends_list[friends_list_n++] = B;
  }
  gen_events (friends_list, friends_list_n);

  long long fsz = -1;
  write (fd[1], &fsz, sizeof (long long));


  int header_size = sizeof (int) * (cnt + 2) + sizeof (long long);
  fsz = header_size;
  l_len = qmalloc0 (header_size);
  l_len[0] = cnt + 1;

  assert (lseek (fd[1], header_size, SEEK_SET) == header_size);

  for (i = 0; i <= cnt; i++) {
    l_len[i + 1] = v[i].n * sizeof (int);
    fsz += v[i].n * sizeof (int);
    my_write (v[i].mem, v[i].n * sizeof (int));
  }
  flush_w_buff();

  assert (lseek (fd[1], 0, SEEK_SET) == 0);
  write (fd[1], &fsz, sizeof (long long));
  write (fd[1], l_len, header_size - sizeof (long long));

  return 0;
}