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
 double MEDIUM_REQUEST_DELAY ; 
 double* REQUEST_DELAY ; 
 double SLOW_REQUEST_DELAY ; 
 int /*<<< orphan*/  assert (int) ; 
 double drand48 () ; 
 double log (double) ; 

void generate_delays (void) {
  double e = drand48 ();
  if (e < 0.1) {
    e = 0.1;
  }
  e = -log (e);
  assert (e >= 0);
  REQUEST_DELAY[0] = SLOW_REQUEST_DELAY * e;
  REQUEST_DELAY[1] = MEDIUM_REQUEST_DELAY * e;
  REQUEST_DELAY[2] = -0.1;
}