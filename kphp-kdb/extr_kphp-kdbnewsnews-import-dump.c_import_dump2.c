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
 int O_APPEND ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 char* cur_write_name ; 
 int /*<<< orphan*/  eat_whitespaces () ; 
 int /*<<< orphan*/  flush_write (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  generate_write_name (int) ; 
 scalar_t__ import_fd ; 
 char* import_file ; 
 int log_split_mod ; 
 int new_type (int) ; 
 scalar_t__ open (char*,int,...) ; 
 int read_int () ; 
 scalar_t__ rend ; 
 scalar_t__ rptr ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ valid_type (int) ; 
 int verbosity ; 
 int /*<<< orphan*/ * wptr ; 
 int /*<<< orphan*/ * write_buff ; 
 int /*<<< orphan*/  write_event (int,int,int,int) ; 
 scalar_t__* write_fd ; 
 int /*<<< orphan*/  write_stat () ; 

int import_dump2 (void) {

  //int prev_time = 0;
  import_fd = open (import_file, O_RDONLY);
  if (import_fd < 0) {
    fprintf (stderr, "Can not open dump (file %s)\n", import_file);
    return 1;
  }
  int i;
  for (i = 0; i < log_split_mod; i++) {
    generate_write_name (i);
    //write_fd[i] = open (cur_write_name, O_CREAT  | O_APPEND, 0644);
    write_fd[i] = open (cur_write_name,  O_APPEND | O_WRONLY | O_CREAT, 0644);
    //fprintf (stderr, "(%d - %d) ", i, write_fd[i]);
    if (write_fd[i] < 0) {
      fprintf (stderr, "can not open file %s for write\n", cur_write_name);
      return 1;
    }
    //fprintf (stderr, "%d - %s\n", i, cur_write_name);
    wptr[i] = write_buff[i];
  }

  int xx = 0;
  while (1) {
    int a,b,c,d,e,f;
    a = read_int (); b = read_int (); c = read_int ();
    d = read_int (); e = read_int (); f = read_int ();
    d = new_type (d);
    if (valid_type (d)) {
      write_event (b, d, f, c);
      xx ++;
    }
    if (verbosity && !(xx & 0xfffff)) {
      fprintf (stderr, "written %d items\n", xx);
    }
    eat_whitespaces ();
    if (rptr == rend) {
      break;
    }

  }
  for (i = 0; i < log_split_mod; i++) {
    flush_write (i);
  }
  if (verbosity) {
    fprintf (stderr, "Total %d bookmarks.\n", xx);
    if (verbosity >= 2) {
      write_stat ();
    }
  }
  return 0;

}