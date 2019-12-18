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
typedef  int /*<<< orphan*/  vector ;
struct TYPE_5__ {int n; int /*<<< orphan*/  mem; } ;

/* Variables and functions */
 int A ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (void*) ; 
 scalar_t__ change_user (char*) ; 
 int engineN ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__* fcurr ; 
 scalar_t__* fd ; 
 int /*<<< orphan*/  flush_w_buff () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * in_name ; 
 int /*<<< orphan*/  init_files (int) ; 
 long long* l_len ; 
 int lseek (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ my_read () ; 
 int /*<<< orphan*/  my_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  open_file (int,int /*<<< orphan*/ *,int) ; 
 void* optarg ; 
 int optind ; 
 int /*<<< orphan*/ * out_name ; 
 char* progname ; 
 TYPE_1__* qmalloc (int) ; 
 long long* qmalloc0 (int) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 
 int userN ; 
 char* username ; 
 TYPE_1__* v ; 
 int /*<<< orphan*/  vct_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vct_init (TYPE_1__*) ; 
 int /*<<< orphan*/  write (scalar_t__,long long*,int) ; 

int main (int argc, char *argv[]) {
  int i;

  set_debug_handlers ();
  progname = argv[0];

  if (argc == 1) {
    usage();
    return 2;
  }

  while ((i = getopt (argc, argv, "hi:o:U:E:u:")) != -1) {
    switch (i) {
    case 'h':
      usage ();
      return 2;
    case 'i':
      in_name = optarg;
      break;
    case 'o':
      out_name = optarg;
      break;
    case 'U':
      userN = atoi (optarg);
      break;
    case 'E':
      engineN = atoi (optarg);
      break;
    case 'u':
      username = optarg;
      break;
    }
  }
  if (argc != optind) {
    usage();
    return 2;
  }

  if (change_user (username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  assert (userN >= 0);
  assert (engineN >= 0);

  init_files (engineN + 1);

  int cnt = userN / engineN;
  v = qmalloc (sizeof (vector) * (cnt + 2));
  assert (v != NULL);

  for (i = 0; i <= cnt; i++) {
    vct_init (&v[i]);
  }

  if (in_name != NULL) {
    open_file (0, in_name, 0);
  } else {
    fd[0] = 0;
  }
  fcurr[0] = 0;

  open_file (1, out_name, 2);

  long long fsz = -1;
  write (fd[1], &fsz, sizeof (long long));

  while (my_read()) {
//    fprintf (stderr, "%d (%d;%d)\n", A, B / 2 , B & 1);
    int x = A / engineN;
    vct_add (&v[x], B);
  }


  int header_size = sizeof (int) * (cnt + 2) + sizeof (long long);
  fsz = header_size;
  l_len = qmalloc0 (header_size);
  l_len[0] = cnt + 1;

  assert (lseek (fd[1], header_size, SEEK_SET) == header_size);

  for (i = 0; i <= cnt; i++) {
  //  fprintf (stderr, "%d/%d\n", i, cnt);
    //qsort (v[i].mem, v[i].n, sizeof (int), cmp_int_inv);


    //l_len[i + 1] = LIST_ (encode) (v[i].mem, v[i].n, 2 * userN + 1, list_buff);

    //my_write (list_buff, l_len[i + 1]);
    //fsz += l_len[i + 1];

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