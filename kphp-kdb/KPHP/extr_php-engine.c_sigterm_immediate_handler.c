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
typedef  int /*<<< orphan*/  message ;

/* Variables and functions */
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  kwrite (int,char const*,int) ; 

__attribute__((used)) static void sigterm_immediate_handler (const int sig) {
  const char message[] = "SIGTERM handled immediately.\n";
  kwrite (2, message, sizeof (message) - (size_t)1);

  _exit (1);
}