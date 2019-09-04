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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

bool
start_thread(void* threads, size_t i, void *(*start_routine) (void *), void *arg) {
    int rc;
    if ((rc = pthread_create(((pthread_t*)threads) + i, NULL, start_routine, arg))) {
        fprintf(stderr, "Failed to create thread, with error: %s\n", strerror(rc));
        return false;
    }
    return true;
}