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
struct connection {int dummy; } ;
typedef  int /*<<< orphan*/  message ;

/* Variables and functions */
 int /*<<< orphan*/  BYS_MSG (struct connection*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int mcs_init_accepted (struct connection*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int bayes_engine_init_accepted (struct connection *c) {
  if (verbosity > 1) {
    fprintf (stderr, "bayes_engine_init_accepted\n");
  }
  memset (BYS_MSG (c), 0, sizeof (message));
  return mcs_init_accepted (c);
}