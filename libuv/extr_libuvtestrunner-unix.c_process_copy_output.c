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
struct TYPE_3__ {int /*<<< orphan*/  stdout_file; } ;
typedef  TYPE_1__ process_info_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_lines (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int process_copy_output(process_info_t* p, FILE* stream) {
  char buf[1024];
  int r;

  r = fseek(p->stdout_file, 0, SEEK_SET);
  if (r < 0) {
    perror("fseek");
    return -1;
  }

  /* TODO: what if the line is longer than buf */
  while (fgets(buf, sizeof(buf), p->stdout_file) != NULL)
    print_lines(buf, strlen(buf), stream);

  if (ferror(p->stdout_file)) {
    perror("read");
    return -1;
  }

  return 0;
}