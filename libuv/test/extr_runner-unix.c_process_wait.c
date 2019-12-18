#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_7__ {int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ process_info_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_8__ {int n; int* pipe; TYPE_1__* vec; } ;
typedef  TYPE_2__ dowait_args ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dowait (TYPE_2__*) ; 
 scalar_t__ errno ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pipe (int*) ; 
 scalar_t__ pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setstacksize (int /*<<< orphan*/ *,int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (TYPE_2__*),TYPE_2__*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int process_wait(process_info_t* vec, int n, int timeout) {
  int i;
  int r;
  int retval;
  process_info_t* p;
  dowait_args args;
  pthread_t tid;
  pthread_attr_t attr;
  unsigned int elapsed_ms;
  struct timeval timebase;
  struct timeval tv;
  fd_set fds;

  args.vec = vec;
  args.n = n;
  args.pipe[0] = -1;
  args.pipe[1] = -1;

  /* The simple case is where there is no timeout */
  if (timeout == -1) {
    dowait(&args);
    return 0;
  }

  /* Hard case. Do the wait with a timeout.
   *
   * Assumption: we are the only ones making this call right now. Otherwise
   * we'd need to lock vec.
   */

  r = pipe((int*)&(args.pipe));
  if (r) {
    perror("pipe()");
    return -1;
  }

  if (pthread_attr_init(&attr))
    abort();

#if defined(__MVS__)
  if (pthread_attr_setstacksize(&attr, 1024 * 1024))
#else
  if (pthread_attr_setstacksize(&attr, 256 * 1024))
#endif
    abort();

  r = pthread_create(&tid, &attr, dowait, &args);

  if (pthread_attr_destroy(&attr))
    abort();

  if (r) {
    perror("pthread_create()");
    retval = -1;
    goto terminate;
  }

  if (gettimeofday(&timebase, NULL))
    abort();

  tv = timebase;
  for (;;) {
    /* Check that gettimeofday() doesn't jump back in time. */
    assert(tv.tv_sec > timebase.tv_sec ||
           (tv.tv_sec == timebase.tv_sec && tv.tv_usec >= timebase.tv_usec));

    elapsed_ms =
        (tv.tv_sec - timebase.tv_sec) * 1000 +
        (tv.tv_usec / 1000) -
        (timebase.tv_usec / 1000);

    r = 0;  /* Timeout. */
    if (elapsed_ms >= (unsigned) timeout)
      break;

    tv.tv_sec = (timeout - elapsed_ms) / 1000;
    tv.tv_usec = (timeout - elapsed_ms) % 1000 * 1000;

    FD_ZERO(&fds);
    FD_SET(args.pipe[0], &fds);

    r = select(args.pipe[0] + 1, &fds, NULL, NULL, &tv);
    if (!(r == -1 && errno == EINTR))
      break;

    if (gettimeofday(&tv, NULL))
      abort();
  }

  if (r == -1) {
    perror("select()");
    retval = -1;

  } else if (r) {
    /* The thread completed successfully. */
    retval = 0;

  } else {
    /* Timeout. Kill all the children. */
    for (i = 0; i < n; i++) {
      p = (process_info_t*)(vec + i * sizeof(process_info_t));
      kill(p->pid, SIGTERM);
    }
    retval = -2;
  }

  if (pthread_join(tid, NULL))
    abort();

terminate:
  close(args.pipe[0]);
  close(args.pipe[1]);
  return retval;
}