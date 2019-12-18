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
 int N_PARAM ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 

__attribute__((used)) static void *f_thread(void *unused) {
	int i;
	for (i = 0; i < N_PARAM; i++) {
		void *p = malloc(100);
		memset(p, 100, 1);
		free(p);
	}

	return NULL;
}