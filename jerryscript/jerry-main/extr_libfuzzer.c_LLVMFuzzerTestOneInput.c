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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;
typedef  int /*<<< orphan*/  jerry_size_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  JERRY_PARSE_NO_OPTS ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 scalar_t__ jerry_is_valid_utf8_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_run_all_enqueued_jobs () ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 

int LLVMFuzzerTestOneInput (const uint8_t *data, size_t size)
{
  srand (0);
  jerry_init (JERRY_INIT_EMPTY);

  if (jerry_is_valid_utf8_string ((jerry_char_t *) data, (jerry_size_t) size))
  {
    jerry_value_t parse_value = jerry_parse (NULL, 0, (jerry_char_t *) data, size, JERRY_PARSE_NO_OPTS);

    if (!jerry_value_is_error (parse_value))
    {
      jerry_value_t run_value = jerry_run (parse_value);
      jerry_release_value (run_value);

      jerry_value_t run_queue_value = jerry_run_all_enqueued_jobs ();
      jerry_release_value (run_queue_value);
    }

    jerry_release_value (parse_value);
  }

  jerry_cleanup ();

  return 0;
}