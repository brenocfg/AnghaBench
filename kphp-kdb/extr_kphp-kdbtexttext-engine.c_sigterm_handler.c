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
 int SIGTERM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int pending_signals ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_immediate_handler ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void sigterm_handler (const int sig) {
  fprintf (stderr, "SIGTERM handled.\n");
  pending_signals |= (1 << SIGTERM);
  signal(SIGTERM, sigterm_immediate_handler);
}