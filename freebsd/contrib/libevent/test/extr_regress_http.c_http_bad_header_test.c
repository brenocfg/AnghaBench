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
struct evkeyvalq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (struct evkeyvalq*) ; 
 int evhttp_add_header (struct evkeyvalq*,char*,char*) ; 
 int /*<<< orphan*/  evhttp_clear_headers (struct evkeyvalq*) ; 
 int /*<<< orphan*/  tt_want (int) ; 

__attribute__((used)) static void
http_bad_header_test(void *ptr)
{
	struct evkeyvalq headers;

	TAILQ_INIT(&headers);

	tt_want(evhttp_add_header(&headers, "One", "Two") == 0);
	tt_want(evhttp_add_header(&headers, "One", "Two\r\n Three") == 0);
	tt_want(evhttp_add_header(&headers, "One\r", "Two") == -1);
	tt_want(evhttp_add_header(&headers, "One\n", "Two") == -1);
	tt_want(evhttp_add_header(&headers, "One", "Two\r") == -1);
	tt_want(evhttp_add_header(&headers, "One", "Two\n") == -1);

	evhttp_clear_headers(&headers);
}