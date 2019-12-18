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
struct WSAData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int NUM_CLIENTS ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int WSAStartup (int /*<<< orphan*/ ,struct WSAData*) ; 
 int closed_connections ; 
 int disconnects ; 
 int spurious_writable_wakeups ; 
 int /*<<< orphan*/  start_client () ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int valid_writable_wakeups ; 

__attribute__((used)) static void start_poll_test(void) {
  int i, r;

#ifdef _WIN32
  {
    struct WSAData wsa_data;
    int r = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    ASSERT(r == 0);
  }
#endif

  start_server();

  for (i = 0; i < NUM_CLIENTS; i++)
    start_client();

  r = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  ASSERT(r == 0);

  /* Assert that at most five percent of the writable wakeups was spurious. */
  ASSERT(spurious_writable_wakeups == 0 ||
         (valid_writable_wakeups + spurious_writable_wakeups) /
         spurious_writable_wakeups > 20);

  ASSERT(closed_connections == NUM_CLIENTS * 2);
#if !defined(__sun) && !defined(_AIX) && !defined(__MVS__)
  ASSERT(disconnects == NUM_CLIENTS * 2);
#endif
  MAKE_VALGRIND_HAPPY();
}