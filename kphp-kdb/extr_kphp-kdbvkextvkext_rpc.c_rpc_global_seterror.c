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
 int /*<<< orphan*/  ADD_MALLOC (scalar_t__) ; 
 int error_verbosity ; 
 int global_errnum ; 
 char const* global_error ; 
 int /*<<< orphan*/  print_backtrace () ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  zzfree (char const*,scalar_t__) ; 

__attribute__((used)) static void rpc_global_seterror (const char *error, int errnum) { /* {{{ */
  if (error) {
    //fprintf (stderr, "error %s #%d\n", error, errnum);
    if (global_error) {
      zzfree (global_error, strlen (global_error) + 1);
    }
    global_error = strdup (error);
    ADD_MALLOC (strlen (error) + 1);
    global_errnum = errnum;
    if (error && error_verbosity >= 1) {
      printf ("Error %s (error_code %d)\n", error, errnum);
      if (error_verbosity >= 2) {
        print_backtrace ();
      }
    }
  }
}