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
struct service_cmd {char const* method; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_headers (struct strbuf*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  hdr_nocache (struct strbuf*) ; 
 int /*<<< orphan*/  hdr_str (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  http_status (struct strbuf*,int,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int bad_request(struct strbuf *hdr, const struct service_cmd *c)
{
	const char *proto = getenv("SERVER_PROTOCOL");

	if (proto && !strcmp(proto, "HTTP/1.1")) {
		http_status(hdr, 405, "Method Not Allowed");
		hdr_str(hdr, "Allow",
			!strcmp(c->method, "GET") ? "GET, HEAD" : c->method);
	} else
		http_status(hdr, 400, "Bad Request");
	hdr_nocache(hdr);
	end_headers(hdr);
	return 0;
}