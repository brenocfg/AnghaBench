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
 long long* I ; 
 scalar_t__* S ; 
 int /*<<< orphan*/  do_store (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long long,long long,long long) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 char* write_buffer ; 

void process_api_uvars_row (void) {
  long long id = I[0];
  char *data = (char*)S[1];
  long long api_id = id / 1000000000000ll; // 10^12
  long long user_id = id / 1000 % 1000000000;
  long long var_id = id % 1000;
  sprintf (write_buffer, "lu%lld.%lld.%lld", user_id, api_id, var_id);
  if (verbosity > 1) {
    fprintf (stderr, "store: %s\n", write_buffer);
  }
  do_store (write_buffer, data);
}