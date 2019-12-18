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
struct test_eloop {int* pipefd2; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eloop_register_read_sock (int,int /*<<< orphan*/ ,struct test_eloop*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_test_read_2_wrong ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (int) ; 
 int /*<<< orphan*/  errno ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void reopen_pipefd2(struct test_eloop *t)
{
	if (t->pipefd2[0] < 0) {
		wpa_printf(MSG_INFO, "pipefd2 had been closed");
	} else {
		int res;

		wpa_printf(MSG_INFO, "close pipefd2");
		eloop_unregister_read_sock(t->pipefd2[0]);
		close(t->pipefd2[0]);
		t->pipefd2[0] = -1;
		close(t->pipefd2[1]);
		t->pipefd2[1] = -1;

		res = pipe(t->pipefd2);
		if (res < 0) {
			wpa_printf(MSG_INFO, "pipe: %s", strerror(errno));
			t->pipefd2[0] = -1;
			t->pipefd2[1] = -1;
			return;
		}

		wpa_printf(MSG_INFO,
			   "re-register pipefd2 with new sockets %d,%d",
			   t->pipefd2[0], t->pipefd2[1]);
		eloop_register_read_sock(t->pipefd2[0], eloop_test_read_2_wrong,
					 t, NULL);
	}
}