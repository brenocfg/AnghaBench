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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct http_get_options {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HTTP_ERROR ; 
 int HTTP_OK ; 
 int /*<<< orphan*/  HTTP_REQUEST_FILE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ finalize_object_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int http_request_reauth (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct http_get_options*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int http_get_file(const char *url, const char *filename,
			 struct http_get_options *options)
{
	int ret;
	struct strbuf tmpfile = STRBUF_INIT;
	FILE *result;

	strbuf_addf(&tmpfile, "%s.temp", filename);
	result = fopen(tmpfile.buf, "a");
	if (!result) {
		error("Unable to open local file %s", tmpfile.buf);
		ret = HTTP_ERROR;
		goto cleanup;
	}

	ret = http_request_reauth(url, result, HTTP_REQUEST_FILE, options);
	fclose(result);

	if (ret == HTTP_OK && finalize_object_file(tmpfile.buf, filename))
		ret = HTTP_ERROR;
cleanup:
	strbuf_release(&tmpfile);
	return ret;
}