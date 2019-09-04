#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct process_id {int dummy; } ;
struct TYPE_6__ {scalar_t__ ip; scalar_t__ port; scalar_t__ pid; scalar_t__ utime; } ;
typedef  TYPE_1__ npid_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (TYPE_1__*,TYPE_1__*,int) ; 

int matches_pid (npid_t *X, npid_t *Y) {
  if (!memcmp (X, Y, sizeof (struct process_id))) {
    return 2;
  } else if ((!Y->ip || X->ip == Y->ip) && (!Y->port || X->port == Y->port) && (!Y->pid || X->pid == Y->pid) && (!Y->utime || X->utime == Y->utime)) {
    return 1;
  } else {
    return 0;
  }
}