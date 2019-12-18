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
struct scm {unsigned int num_fds; int /*<<< orphan*/ * fds; } ;

/* Variables and functions */
 int /*<<< orphan*/  fd_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct scm*) ; 

__attribute__((used)) static void scm_free(struct scm *scm) {
    for (unsigned i = 0; i < scm->num_fds; i++)
        fd_close(scm->fds[i]);
    free(scm);
}