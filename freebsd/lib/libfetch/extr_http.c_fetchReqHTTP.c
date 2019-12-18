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
struct url {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  http_get_proxy (struct url*,char const*) ; 
 int /*<<< orphan*/ * http_request_body (struct url*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*) ; 

FILE *
fetchReqHTTP(struct url *URL, const char *method, const char *flags,
	const char *content_type, const char *body)
{

	return (http_request_body(URL, method, NULL, http_get_proxy(URL, flags),
	    flags, content_type, body));
}