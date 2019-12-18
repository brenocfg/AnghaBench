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
struct strbuf {char* buf; scalar_t__ len; } ;
struct object_id {int dummy; } ;
struct bundle_header {int /*<<< orphan*/  references; int /*<<< orphan*/  prerequisites; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_to_ref_list (struct object_id*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bundle_signature ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  isspace (char const) ; 
 scalar_t__ parse_oid_hex (char*,struct object_id*,char const**) ; 
 scalar_t__ strbuf_getwholeline_fd (struct strbuf*,int,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_bundle_header(int fd, struct bundle_header *header,
			       const char *report_path)
{
	struct strbuf buf = STRBUF_INIT;
	int status = 0;

	/* The bundle header begins with the signature */
	if (strbuf_getwholeline_fd(&buf, fd, '\n') ||
	    strcmp(buf.buf, bundle_signature)) {
		if (report_path)
			error(_("'%s' does not look like a v2 bundle file"),
			      report_path);
		status = -1;
		goto abort;
	}

	/* The bundle header ends with an empty line */
	while (!strbuf_getwholeline_fd(&buf, fd, '\n') &&
	       buf.len && buf.buf[0] != '\n') {
		struct object_id oid;
		int is_prereq = 0;
		const char *p;

		if (*buf.buf == '-') {
			is_prereq = 1;
			strbuf_remove(&buf, 0, 1);
		}
		strbuf_rtrim(&buf);

		/*
		 * Tip lines have object name, SP, and refname.
		 * Prerequisites have object name that is optionally
		 * followed by SP and subject line.
		 */
		if (parse_oid_hex(buf.buf, &oid, &p) ||
		    (*p && !isspace(*p)) ||
		    (!is_prereq && !*p)) {
			if (report_path)
				error(_("unrecognized header: %s%s (%d)"),
				      (is_prereq ? "-" : ""), buf.buf, (int)buf.len);
			status = -1;
			break;
		} else {
			if (is_prereq)
				add_to_ref_list(&oid, "", &header->prerequisites);
			else
				add_to_ref_list(&oid, p + 1, &header->references);
		}
	}

 abort:
	if (status) {
		close(fd);
		fd = -1;
	}
	strbuf_release(&buf);
	return fd;
}