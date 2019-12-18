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
 scalar_t__ ERR ; 
 scalar_t__ LogFD ; 
 int /*<<< orphan*/  close (scalar_t__) ; 

void
log_close() {
	if (LogFD != ERR) {
		close(LogFD);
		LogFD = ERR;
	}
}