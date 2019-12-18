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
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * logbuffer ; 
 int /*<<< orphan*/  logbuffer_shm ; 
 int /*<<< orphan*/  shm_unlink (char*) ; 
 char* shmlogname ; 

void close_logbuffer(void) {
    close(logbuffer_shm);
    shm_unlink(shmlogname);
    free(shmlogname);
    logbuffer = NULL;
    shmlogname = "";
}