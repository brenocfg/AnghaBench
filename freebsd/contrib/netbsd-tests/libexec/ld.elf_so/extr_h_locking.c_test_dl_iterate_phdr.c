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
 int /*<<< orphan*/  RTLD_LAZY ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ dl_iterate_phdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_iterate_phdr_cb ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dlsym (void*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sleep_fini ; 
 scalar_t__ sleep_init ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_dl_iterate_phdr_helper ; 
 int /*<<< orphan*/ * tls_callback_sym ; 

__attribute__((used)) static void
test_dl_iterate_phdr(void)
{
	pthread_t t;
	void *dso;
	sleep_init = 0;
	sleep_fini = 0;
	if ((dso = dlopen("libh_helper_dso2.so", RTLD_LAZY)) == NULL) {
		fprintf(stderr, "opening helper failed\n");
		_exit(1);
	}
	tls_callback_sym = dlsym(dso, "tls_callback");
	if (tls_callback_sym == NULL) {
		fprintf(stderr, "bad helper\n");
		_exit(1);
	}
	pthread_create(&t, NULL, test_dl_iterate_phdr_helper, NULL);
	if (dl_iterate_phdr(dl_iterate_phdr_cb, NULL))
		_exit(1);
	_exit(0);
}