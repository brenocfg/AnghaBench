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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 scalar_t__ ESRCH ; 
 int /*<<< orphan*/  SIGHUP ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  getpgid (int /*<<< orphan*/ ) ; 
 scalar_t__ killpg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static inline void
hangup(pid_t pid) {
    errno = 0;
    pid_t pgid = getpgid(pid);
    if (errno == ESRCH) return;
    if (errno != 0) { perror("Failed to get process group id for child"); return; }
    if (killpg(pgid, SIGHUP) != 0) {
        if (errno != ESRCH) perror("Failed to kill child");
    }
}