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
 int backtrace (void**,int) ; 
 int /*<<< orphan*/  backtrace_symbols_fd (void**,int,int) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

void print_backtrace (void) {
  void *buffer[64];
  int nptrs = backtrace (buffer, 64);
  write (2, "\n------- Stack Backtrace -------\n", 33);
  backtrace_symbols_fd (buffer, nptrs, 2);
  write (2, "-------------------------------\n", 32);
}