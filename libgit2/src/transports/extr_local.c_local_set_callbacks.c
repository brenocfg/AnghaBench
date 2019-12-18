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
struct TYPE_2__ {void* message_cb_payload; void* error_cb; void* progress_cb; } ;
typedef  TYPE_1__ transport_local ;
typedef  void* git_transport_message_cb ;
typedef  int /*<<< orphan*/  git_transport_certificate_check_cb ;
typedef  int /*<<< orphan*/  git_transport ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int local_set_callbacks(
	git_transport *transport,
	git_transport_message_cb progress_cb,
	git_transport_message_cb error_cb,
	git_transport_certificate_check_cb certificate_check_cb,
	void *message_cb_payload)
{
	transport_local *t = (transport_local *)transport;

	GIT_UNUSED(certificate_check_cb);

	t->progress_cb = progress_cb;
	t->error_cb = error_cb;
	t->message_cb_payload = message_cb_payload;

	return 0;
}