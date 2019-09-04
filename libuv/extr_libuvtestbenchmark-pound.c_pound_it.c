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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  (* setup_fn ) (int,void*) ;
typedef  int /*<<< orphan*/  make_connect_fn ;
typedef  int (* connect_fn ) (int,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 double NANOSEC ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 double closed_streams ; 
 int conns_failed ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,double,int) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  start ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_hrtime () ; 
 int /*<<< orphan*/  uv_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_update_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pound_it(int concurrency,
                    const char* type,
                    setup_fn do_setup,
                    connect_fn do_connect,
                    make_connect_fn make_connect,
                    void* arg) {
  double secs;
  int r;
  uint64_t start_time; /* in ns */
  uint64_t end_time;

  loop = uv_default_loop();

  uv_update_time(loop);
  start = uv_now(loop);

  /* Run benchmark for at least five seconds. */
  start_time = uv_hrtime();

  do_setup(concurrency, arg);

  r = do_connect(concurrency, make_connect, arg);
  ASSERT(!r);

  uv_run(loop, UV_RUN_DEFAULT);

  end_time = uv_hrtime();

  /* Number of fractional seconds it took to run the benchmark. */
  secs = (double)(end_time - start_time) / NANOSEC;

  fprintf(stderr, "%s-conn-pound-%d: %.0f accepts/s (%d failed)\n",
          type,
          concurrency,
          closed_streams / secs,
          conns_failed);
  fflush(stderr);

  MAKE_VALGRIND_HAPPY();
  return 0;
}