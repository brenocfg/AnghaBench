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
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  g_gate_log (int /*<<< orphan*/ ,char*,size_t) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void *
malloc_waitok(size_t size)
{
	void *p;

	while ((p = malloc(size)) == NULL) {
		g_gate_log(LOG_DEBUG, "Cannot allocate %zu bytes.", size);
		sleep(1);
	}
	return (p);
}