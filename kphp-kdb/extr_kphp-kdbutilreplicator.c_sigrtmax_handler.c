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
 int /*<<< orphan*/  kwrite (int,char const*,int) ; 
 int /*<<< orphan*/  sigrtmax_cnt ; 

__attribute__((used)) static void sigrtmax_handler (const int sig) {
  static const char message[] = "got SIGUSR3, incr update related binlog generation number.\n";
  kwrite (2, message, sizeof (message) - (size_t)1);
  sigrtmax_cnt++;
}