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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*,...) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 char* strerror (int) ; 

__attribute__((used)) static int tloop_join(pthread_t thread, const char *name)
{
	int err;
	void *tret;
	err = pthread_join(thread, &tret);
	if (!tret) {
		error(_("%s thread failed"), name);
		return 1;
	}
	if (err) {
		error(_("%s thread failed to join: %s"), name, strerror(err));
		return 1;
	}
	return 0;
}