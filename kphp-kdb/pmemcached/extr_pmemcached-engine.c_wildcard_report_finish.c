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
struct TYPE_3__ {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int) ; 
 int /*<<< orphan*/  memcpy (int,char*,int) ; 
 scalar_t__ metafile_mode ; 
 int /*<<< orphan*/  return_one_key_flags_len (TYPE_1__*,char const*,int,int,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  wildcard_add_value (char const*,int,int,int) ; 
 int /*<<< orphan*/  wildcard_arrays_allocated ; 
 TYPE_1__* wildcard_connection ; 
 int wildcard_ptr ; 
 int wildcard_total_data_sent ; 
 int wildcard_total_keys_sent ; 
 char wildcard_type ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

void wildcard_report_finish (const char *key, int key_len) {
  if (wildcard_type == '#') {
    if (metafile_mode) {
      memcpy (wildcard_ptr + wildcard_total_data_sent, "}", 1);
      wildcard_total_data_sent ++;
    } else {
      wildcard_total_data_sent ++;
      write_out (&wildcard_connection->Out, "}\r\n", 3);
    }
    if (metafile_mode) {
      static char s[12];
      sprintf (s, "%09d", wildcard_total_keys_sent);
      memcpy (wildcard_ptr + 2, s, 9);
      return_one_key_flags_len (wildcard_connection, key, key_len, wildcard_ptr, wildcard_total_data_sent, 1);
      wildcard_add_value (key, key_len - 1, wildcard_ptr, wildcard_total_data_sent);
      free (wildcard_ptr);
      wildcard_arrays_allocated --;
    } else {
      static char s[12];
      sprintf (s, "%09d", wildcard_total_data_sent);
      memcpy (wildcard_ptr, s, 9);
      sprintf (s, "%09d", wildcard_total_keys_sent);
      memcpy (wildcard_ptr + 13, s, 9);
    }
  }
}