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
typedef  int /*<<< orphan*/  process_info_t ;

/* Variables and functions */
#define  TEST_OK 129 
#define  TEST_SKIP 128 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,char const*,char const*,char*) ; 
 scalar_t__ process_output_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_read_last_line (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 

void log_tap_result(int test_count,
                    const char* test,
                    int status,
                    process_info_t* process) {
  const char* result;
  const char* directive;
  char reason[1024];
  int reason_length;

  switch (status) {
  case TEST_OK:
    result = "ok";
    directive = "";
    break;
  case TEST_SKIP:
    result = "ok";
    directive = " # SKIP ";
    break;
  default:
    result = "not ok";
    directive = "";
  }

  if (status == TEST_SKIP && process_output_size(process) > 0) {
    process_read_last_line(process, reason, sizeof reason);
    reason_length = strlen(reason);
    if (reason_length > 0 && reason[reason_length - 1] == '\n')
      reason[reason_length - 1] = '\0';
  } else {
    reason[0] = '\0';
  }

  fprintf(stderr, "%s %d - %s%s%s\n", result, test_count, test, directive, reason);
  fflush(stderr);
}