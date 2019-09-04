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
struct strbuf {int dummy; } ;
struct http_get_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_REQUEST_STRBUF ; 
 int http_request_reauth (char const*,struct strbuf*,int /*<<< orphan*/ ,struct http_get_options*) ; 

int http_get_strbuf(const char *url,
		    struct strbuf *result,
		    struct http_get_options *options)
{
	return http_request_reauth(url, result, HTTP_REQUEST_STRBUF, options);
}