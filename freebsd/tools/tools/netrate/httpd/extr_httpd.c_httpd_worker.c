#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct httpd_thread_statep {int /*<<< orphan*/  hts_fd; } ;
struct TYPE_2__ {int /*<<< orphan*/  listen_sock; } ;

/* Variables and functions */
 int accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  http_serve (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* statep ; 

__attribute__((used)) static void *
httpd_worker(void *arg)
{
	struct httpd_thread_statep *htsp;
	int sock;

	htsp = arg;

	while (1) {
		sock = accept(statep->listen_sock, NULL, NULL);
		if (sock < 0)
			continue;
		(void)http_serve(sock, htsp->hts_fd);
		close(sock);
	}
}