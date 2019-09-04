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
struct rpc_service {char* name; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  content_type ; 
 scalar_t__ determine_protocol_version_server () ; 
 int /*<<< orphan*/  end_headers (struct strbuf*) ; 
 int /*<<< orphan*/  for_each_namespaced_ref (int /*<<< orphan*/ ,struct strbuf*) ; 
 char* get_parameter (char*) ; 
 int /*<<< orphan*/  hdr_nocache (struct strbuf*) ; 
 int /*<<< orphan*/  hdr_str (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_flush (int) ; 
 int /*<<< orphan*/  packet_write_fmt (int,char*,char*) ; 
 scalar_t__ protocol_v2 ; 
 int /*<<< orphan*/  run_service (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_getanyfile (struct strbuf*) ; 
 struct rpc_service* select_service (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  send_strbuf (struct strbuf*,char*,struct strbuf*) ; 
 int /*<<< orphan*/  show_text_ref ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void get_info_refs(struct strbuf *hdr, char *arg)
{
	const char *service_name = get_parameter("service");
	struct strbuf buf = STRBUF_INIT;

	hdr_nocache(hdr);

	if (service_name) {
		const char *argv[] = {NULL /* service name */,
			"--stateless-rpc", "--advertise-refs",
			".", NULL};
		struct rpc_service *svc = select_service(hdr, service_name);

		strbuf_addf(&buf, "application/x-git-%s-advertisement",
			svc->name);
		hdr_str(hdr, content_type, buf.buf);
		end_headers(hdr);


		if (determine_protocol_version_server() != protocol_v2) {
			packet_write_fmt(1, "# service=git-%s\n", svc->name);
			packet_flush(1);
		}

		argv[0] = svc->name;
		run_service(argv, 0);

	} else {
		select_getanyfile(hdr);
		for_each_namespaced_ref(show_text_ref, &buf);
		send_strbuf(hdr, "text/plain", &buf);
	}
	strbuf_release(&buf);
}