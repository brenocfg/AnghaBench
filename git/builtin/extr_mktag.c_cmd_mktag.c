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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strbuf_read (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  tag_type ; 
 int /*<<< orphan*/  usage (char*) ; 
 scalar_t__ verify_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 

int cmd_mktag(int argc, const char **argv, const char *prefix)
{
	struct strbuf buf = STRBUF_INIT;
	struct object_id result;

	if (argc != 1)
		usage("git mktag");

	if (strbuf_read(&buf, 0, 4096) < 0) {
		die_errno("could not read from stdin");
	}

	/* Verify it for some basic sanity: it needs to start with
	   "object <sha1>\ntype\ntagger " */
	if (verify_tag(buf.buf, buf.len) < 0)
		die("invalid tag signature file");

	if (write_object_file(buf.buf, buf.len, tag_type, &result) < 0)
		die("unable to write tag file");

	strbuf_release(&buf);
	printf("%s\n", oid_to_hex(&result));
	return 0;
}