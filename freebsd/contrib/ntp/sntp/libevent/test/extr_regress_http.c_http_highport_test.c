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
struct evhttp {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ evhttp_bind_socket (struct evhttp*,char*,int) ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 struct evhttp* evhttp_new (int /*<<< orphan*/ ) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_fail_msg (char*) ; 

__attribute__((used)) static void
http_highport_test(void *arg)
{
	struct basic_test_data *data = arg;
	int i = -1;
	struct evhttp *myhttp = NULL;

	/* Try a few different ports */
	for (i = 0; i < 50; ++i) {
		myhttp = evhttp_new(data->base);
		if (evhttp_bind_socket(myhttp, "127.0.0.1", 65535 - i) == 0) {
			test_ok = 1;
			evhttp_free(myhttp);
			return;
		}
		evhttp_free(myhttp);
	}

	tt_fail_msg("Couldn't get a high port");
}