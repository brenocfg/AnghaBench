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
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) (int const)) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void sigusr1_handler (const int sig) {
  fprintf(stderr, "got SIGUSR1, rotate logs.\n");
  signal(SIGUSR1, sigusr1_handler);
}