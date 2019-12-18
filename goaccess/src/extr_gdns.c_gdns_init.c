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
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  not_full; int /*<<< orphan*/  not_empty; } ;
typedef  int /*<<< orphan*/  GDnsQueue ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/  QUEUE_SIZE ; 
 int /*<<< orphan*/  gdns_queue ; 
 TYPE_1__ gdns_thread ; 
 int /*<<< orphan*/  gqueue_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmalloc (int) ; 

void
gdns_init (void)
{
  gdns_queue = xmalloc (sizeof (GDnsQueue));
  gqueue_init (gdns_queue, QUEUE_SIZE);

  if (pthread_cond_init (&(gdns_thread.not_empty), NULL))
    FATAL ("Failed init thread condition");

  if (pthread_cond_init (&(gdns_thread.not_full), NULL))
    FATAL ("Failed init thread condition");

  if (pthread_mutex_init (&(gdns_thread.mutex), NULL))
    FATAL ("Failed init thread mutex");
}