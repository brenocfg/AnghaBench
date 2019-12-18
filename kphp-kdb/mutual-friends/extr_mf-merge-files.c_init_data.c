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
 int MY_BUFF_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int engineN ; 
 int exceptionsI ; 
 char* exceptions_name ; 
 void** f_buff ; 
 void* f_buff_i ; 
 void* f_buff_r ; 
 void* f_buff_size ; 
 int** f_header ; 
 int* fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,long long,long long) ; 
 int friendsI ; 
 char* friends_name ; 
 long long* fsize ; 
 scalar_t__ open_file (int,char*,int) ; 
 void* qmalloc (int) ; 
 void* qmalloc0 (int) ; 
 int /*<<< orphan*/  read (int,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char*) ; 
 int un ; 

void init_data (void) {
  char fname[50];
  int i;

  f_buff = qmalloc (sizeof (unsigned char *) * engineN);
  f_header = qmalloc (sizeof (int *) * engineN);

  f_buff_size = qmalloc0 (sizeof (int) * engineN);
  f_buff_r = qmalloc0 (sizeof (int) * engineN);
  f_buff_i = qmalloc0 (sizeof (int) * engineN);

  for (i = 0; i < engineN; i++) {
    sprintf (fname, "from%03d", i);
    if (open_file (i, fname, -1) < 0) {
      fd[i] = -1;
      continue;
    }
    f_buff[i] = qmalloc (sizeof (unsigned char) * MY_BUFF_SIZE);

    long long fsz;
    read (fd[i], &fsz, sizeof (long long));
    if (fsz != fsize[i]) {
      fprintf (stderr, "something wrong with file <%s> : wrong size %lld (%lld expected)\n", fname, fsize[i], fsz);
    }
    assert (fsz == fsize[i]);


    int cnt;
    read (fd[i], &cnt, sizeof (int));

    assert (cnt == un + 1);
    f_header[i] = qmalloc (sizeof (int) * cnt);
    read (fd[i], f_header[i], sizeof (int) * cnt);
  }
  if (strlen (friends_name) > 0) {
    open_file (friendsI, friends_name, 0);
  }
  if (strlen (exceptions_name) > 0) {
    open_file (exceptionsI, exceptions_name, 0);
  }
}