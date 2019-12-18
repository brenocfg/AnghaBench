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
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SIZE_ARG (size_t) ; 
 int /*<<< orphan*/  EV_SIZE_FMT ; 
 int /*<<< orphan*/  evhttp_add_header (struct evkeyvalq*,char*,char*) ; 
 int /*<<< orphan*/ * evhttp_find_header (struct evkeyvalq*,char*) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evhttp_maybe_add_content_length_header(struct evkeyvalq *headers,
    size_t content_length)
{
	if (evhttp_find_header(headers, "Transfer-Encoding") == NULL &&
	    evhttp_find_header(headers,	"Content-Length") == NULL) {
		char len[22];
		evutil_snprintf(len, sizeof(len), EV_SIZE_FMT,
		    EV_SIZE_ARG(content_length));
		evhttp_add_header(headers, "Content-Length", len);
	}
}