#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int) ; 
 int active_gdns ; 
 int /*<<< orphan*/  dns_worker ; 
 TYPE_1__ gdns_thread ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 

void
gdns_thread_create (void)
{
  int th;

  active_gdns = 1;
  th = pthread_create (&(gdns_thread.thread), NULL, (void *) &dns_worker, NULL);
  if (th)
    FATAL ("Return code from pthread_create(): %d", th);
  pthread_detach (gdns_thread.thread);
}