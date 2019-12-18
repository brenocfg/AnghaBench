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
struct test_eloop {int magic; int close_in_timeout; int /*<<< orphan*/ * pipefd2; int /*<<< orphan*/ * pipefd1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_register_read_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct test_eloop*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct test_eloop*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_test_cb ; 
 int /*<<< orphan*/  eloop_test_read_1 ; 
 int /*<<< orphan*/  eloop_test_read_2 ; 
 int /*<<< orphan*/  eloop_test_timeout ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  os_free (struct test_eloop*) ; 
 int /*<<< orphan*/  os_sleep (int /*<<< orphan*/ ,int) ; 
 struct test_eloop* os_zalloc (int) ; 
 int pipe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void eloop_tests_start(int close_in_timeout)
{
	struct test_eloop *t;
	int res;

	t = os_zalloc(sizeof(*t));
	if (!t)
		return;
	t->magic = 0x12345678;
	t->close_in_timeout = close_in_timeout;

	wpa_printf(MSG_INFO, "starting eloop tests (%p) (close_in_timeout=%d)",
		   t, close_in_timeout);

	res = pipe(t->pipefd1);
	if (res < 0) {
		wpa_printf(MSG_INFO, "pipe: %s", strerror(errno));
		os_free(t);
		return;
	}

	res = pipe(t->pipefd2);
	if (res < 0) {
		wpa_printf(MSG_INFO, "pipe: %s", strerror(errno));
		close(t->pipefd1[0]);
		close(t->pipefd1[1]);
		os_free(t);
		return;
	}

	wpa_printf(MSG_INFO, "pipe fds: %d,%d %d,%d",
		   t->pipefd1[0], t->pipefd1[1],
		   t->pipefd2[0], t->pipefd2[1]);

	eloop_register_read_sock(t->pipefd1[0], eloop_test_read_1, t, NULL);
	eloop_register_read_sock(t->pipefd2[0], eloop_test_read_2, t, NULL);
	eloop_register_timeout(0, 0, eloop_test_cb, t, NULL);
	eloop_register_timeout(0, 200000, eloop_test_timeout, t, NULL);

	if (write(t->pipefd1[1], "HELLO", 5) < 0)
		wpa_printf(MSG_INFO, "write: %s", strerror(errno));
	if (write(t->pipefd2[1], "TEST", 4) < 0)
		wpa_printf(MSG_INFO, "write: %s", strerror(errno));
	os_sleep(0, 50000);
	wpa_printf(MSG_INFO, "waiting for eloop callbacks");
}