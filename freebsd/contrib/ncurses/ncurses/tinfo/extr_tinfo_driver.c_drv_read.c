#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ read_thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  _ifd; } ;
typedef  int /*<<< orphan*/  TERMINAL_CONTROL_BLOCK ;
typedef  TYPE_1__ SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 int /*<<< orphan*/  SetSP () ; 
 TYPE_2__ _nc_globals ; 
 int /*<<< orphan*/  assert (int*) ; 
 scalar_t__ pthread_equal ; 
 scalar_t__ pthread_kill ; 
 scalar_t__ pthread_self () ; 
 int read (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static int
drv_read(TERMINAL_CONTROL_BLOCK * TCB, int *buf)
{
    SCREEN *sp;
    unsigned char c2 = 0;
    int n;

    AssertTCB();
    assert(buf);
    SetSP();

# if USE_PTHREADS_EINTR
    if ((pthread_self) && (pthread_kill) && (pthread_equal))
	_nc_globals.read_thread = pthread_self();
# endif
    n = read(sp->_ifd, &c2, (size_t) 1);
#if USE_PTHREADS_EINTR
    _nc_globals.read_thread = 0;
#endif
    *buf = (int) c2;
    return n;
}