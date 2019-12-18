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
 int /*<<< orphan*/  process_log_file () ; 
 int /*<<< orphan*/  raise (int) ; 
 int /*<<< orphan*/  sigchain_pop (int) ; 

__attribute__((used)) static void process_log_file_on_signal(int signo)
{
	process_log_file();
	sigchain_pop(signo);
	raise(signo);
}