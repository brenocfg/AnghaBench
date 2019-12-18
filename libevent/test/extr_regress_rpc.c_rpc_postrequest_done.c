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
struct kill {int dummy; } ;
struct evhttp_request {scalar_t__ response_code; int /*<<< orphan*/  input_buffer; } ;

/* Variables and functions */
 scalar_t__ HTTP_OK ; 
 int /*<<< orphan*/  event_loopexit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kill_free (struct kill*) ; 
 struct kill* kill_new () ; 
 int kill_unmarshal (struct kill*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int test_ok ; 

__attribute__((used)) static void
rpc_postrequest_done(struct evhttp_request *req, void *arg)
{
	struct kill* kill_reply = NULL;

	if (req->response_code != HTTP_OK) {
		fprintf(stderr, "FAILED (response code)\n");
		exit(1);
	}

	kill_reply = kill_new();

	if ((kill_unmarshal(kill_reply, req->input_buffer)) == -1) {
		fprintf(stderr, "FAILED (unmarshal)\n");
		exit(1);
	}

	kill_free(kill_reply);

	test_ok = 1;
	event_loopexit(NULL);
}