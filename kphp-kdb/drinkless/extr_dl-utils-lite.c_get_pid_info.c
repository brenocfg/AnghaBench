#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {int /*<<< orphan*/  starttime; int /*<<< orphan*/  cstime; int /*<<< orphan*/  cutime; int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; } ;
typedef  TYPE_1__ pid_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int TMEM_SIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dl_assert (int /*<<< orphan*/ ,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ *) ; 

int get_pid_info (pid_t pid, pid_info_t *info) {
#define TMEM_SIZE 10000
  static char mem[TMEM_SIZE];
  snprintf (mem, TMEM_SIZE, "/proc/%lu/stat", (unsigned long)pid);
  int fd = open (mem, O_RDONLY);

  if (fd == -1) {
    return 0;
  }

  int size = (int)read (fd, mem, TMEM_SIZE - 1);
  if (size <= 0) {
    close (fd);
    return 0;
  }
  mem[size] = 0;

  char *s = mem;
  int pass_cnt = 0;

  while (pass_cnt < 22) {
    if (pass_cnt == 12) {
      sscanf (s, "%llu", &info->utime);
    }
    if (pass_cnt == 13) {
      sscanf (s, "%llu", &info->stime);
   }
    if (pass_cnt == 14) {
      sscanf (s, "%llu", &info->cutime);
    }
    if (pass_cnt == 15) {
      sscanf (s, "%llu", &info->cstime);
    }
    if (pass_cnt == 21) {
      sscanf (s, "%llu", &info->starttime);
    }
    while (*s && *s != ' ') {
      s++;
    }
    if (*s == ' ') {
      s++;
      pass_cnt++;
    } else {
      dl_assert (0, "unexpected end of proc file");
      break;
    }
  }

  close (fd);
  return 1;
#undef TMEM_SIZE
}