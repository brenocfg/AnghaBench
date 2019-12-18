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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_4__ {int nr; TYPE_1__* items; } ;
struct TYPE_3__ {int /*<<< orphan*/  string; struct object_id* util; } ;

/* Variables and functions */
 int OBJ_TAG ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fmt_tag_signature (struct strbuf*,struct strbuf*,char*,unsigned long) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__ origins ; 
 unsigned long parse_signature (char*,unsigned long) ; 
 char* read_object_file (struct object_id*,int*,unsigned long*) ; 
 int /*<<< orphan*/  strbuf_add_commented_lines (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ verify_signed_buffer (char*,unsigned long,char*,unsigned long,struct strbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fmt_merge_msg_sigs(struct strbuf *out)
{
	int i, tag_number = 0, first_tag = 0;
	struct strbuf tagbuf = STRBUF_INIT;

	for (i = 0; i < origins.nr; i++) {
		struct object_id *oid = origins.items[i].util;
		enum object_type type;
		unsigned long size, len;
		char *buf = read_object_file(oid, &type, &size);
		struct strbuf sig = STRBUF_INIT;

		if (!buf || type != OBJ_TAG)
			goto next;
		len = parse_signature(buf, size);

		if (size == len)
			; /* merely annotated */
		else if (verify_signed_buffer(buf, len, buf + len, size - len, &sig, NULL)) {
			if (!sig.len)
				strbuf_addstr(&sig, "gpg verification failed.\n");
		}

		if (!tag_number++) {
			fmt_tag_signature(&tagbuf, &sig, buf, len);
			first_tag = i;
		} else {
			if (tag_number == 2) {
				struct strbuf tagline = STRBUF_INIT;
				strbuf_addch(&tagline, '\n');
				strbuf_add_commented_lines(&tagline,
						origins.items[first_tag].string,
						strlen(origins.items[first_tag].string));
				strbuf_insert(&tagbuf, 0, tagline.buf,
					      tagline.len);
				strbuf_release(&tagline);
			}
			strbuf_addch(&tagbuf, '\n');
			strbuf_add_commented_lines(&tagbuf,
					origins.items[i].string,
					strlen(origins.items[i].string));
			fmt_tag_signature(&tagbuf, &sig, buf, len);
		}
		strbuf_release(&sig);
	next:
		free(buf);
	}
	if (tagbuf.len) {
		strbuf_addch(out, '\n');
		strbuf_addbuf(out, &tagbuf);
	}
	strbuf_release(&tagbuf);
}