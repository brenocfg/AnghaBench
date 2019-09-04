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

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,size_t,int /*<<< orphan*/ ) ; 
 int fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

int process_read_last_line(process_info_t *p,
                           char* buffer,
                           size_t buffer_len) {
  char* ptr;

  int r = fseek(p->stdout_file, 0, SEEK_SET);
  if (r < 0) {
    perror("fseek");
    return -1;
  }

  buffer[0] = '\0';

  while (fgets(buffer, buffer_len, p->stdout_file) != NULL) {
    for (ptr = buffer; *ptr && *ptr != '\r' && *ptr != '\n'; ptr++);
    *ptr = '\0';
  }

  if (ferror(p->stdout_file)) {
    perror("read");
    buffer[0] = '\0';
    return -1;
  }
  return 0;
}