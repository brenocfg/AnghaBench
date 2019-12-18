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
struct rpc_service {char* name; int /*<<< orphan*/  buffer_input; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  check_content_type (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  content_type ; 
 int /*<<< orphan*/  end_headers (struct strbuf*) ; 
 int /*<<< orphan*/  hdr_nocache (struct strbuf*) ; 
 int /*<<< orphan*/  hdr_str (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_service (char const**,int /*<<< orphan*/ ) ; 
 struct rpc_service* select_service (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void service_rpc(struct strbuf *hdr, char *service_name)
{
	const char *argv[] = {NULL, "--stateless-rpc", ".", NULL};
	struct rpc_service *svc = select_service(hdr, service_name);
	struct strbuf buf = STRBUF_INIT;

	strbuf_reset(&buf);
	strbuf_addf(&buf, "application/x-git-%s-request", svc->name);
	check_content_type(hdr, buf.buf);

	hdr_nocache(hdr);

	strbuf_reset(&buf);
	strbuf_addf(&buf, "application/x-git-%s-result", svc->name);
	hdr_str(hdr, content_type, buf.buf);

	end_headers(hdr);

	argv[0] = svc->name;
	run_service(argv, svc->buffer_input);
	strbuf_release(&buf);
}