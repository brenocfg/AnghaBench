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
 int /*<<< orphan*/  dl_signal (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kwrite (int,char const*,int) ; 
 int pending_signals ; 
 int /*<<< orphan*/  sigint_immediate_handler ; 

__attribute__((used)) static void sigint_handler (const int sig) {
  const char message[] = "SIGINT handled.\n";
  kwrite (2, message, sizeof (message) - (size_t)1);

  pending_signals |= (1 << sig);
  dl_signal (sig, sigint_immediate_handler);
}