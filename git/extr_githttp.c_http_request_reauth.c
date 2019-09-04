#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct http_get_options {TYPE_2__* effective_url; TYPE_1__* base_url; } ;
struct TYPE_4__ {char* buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int HTTP_OK ; 
 int HTTP_REAUTH ; 
#define  HTTP_REQUEST_FILE 129 
#define  HTTP_REQUEST_STRBUF 128 
 int HTTP_START_FAILED ; 
 int /*<<< orphan*/  credential_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  credential_from_url (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_errno (char*) ; 
 int /*<<< orphan*/  fflush (void*) ; 
 int /*<<< orphan*/  fileno (void*) ; 
 int /*<<< orphan*/  ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_auth ; 
 int http_request (char const*,void*,int,struct http_get_options*) ; 
 int /*<<< orphan*/  rewind (void*) ; 
 int /*<<< orphan*/  strbuf_reset (void*) ; 
 scalar_t__ update_url_from_redirect (TYPE_1__*,char const*,TYPE_2__*) ; 

__attribute__((used)) static int http_request_reauth(const char *url,
			       void *result, int target,
			       struct http_get_options *options)
{
	int ret = http_request(url, result, target, options);

	if (ret != HTTP_OK && ret != HTTP_REAUTH)
		return ret;

	if (options && options->effective_url && options->base_url) {
		if (update_url_from_redirect(options->base_url,
					     url, options->effective_url)) {
			credential_from_url(&http_auth, options->base_url->buf);
			url = options->effective_url->buf;
		}
	}

	if (ret != HTTP_REAUTH)
		return ret;

	/*
	 * The previous request may have put cruft into our output stream; we
	 * should clear it out before making our next request.
	 */
	switch (target) {
	case HTTP_REQUEST_STRBUF:
		strbuf_reset(result);
		break;
	case HTTP_REQUEST_FILE:
		if (fflush(result)) {
			error_errno("unable to flush a file");
			return HTTP_START_FAILED;
		}
		rewind(result);
		if (ftruncate(fileno(result), 0) < 0) {
			error_errno("unable to truncate a file");
			return HTTP_START_FAILED;
		}
		break;
	default:
		BUG("Unknown http_request target");
	}

	credential_fill(&http_auth);

	return http_request(url, result, target, options);
}