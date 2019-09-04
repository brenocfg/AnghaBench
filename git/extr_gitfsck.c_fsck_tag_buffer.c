#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct tag {TYPE_1__ object; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct fsck_options {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  FSCK_MSG_BAD_OBJECT_SHA1 ; 
 int /*<<< orphan*/  FSCK_MSG_BAD_TAG_NAME ; 
 int /*<<< orphan*/  FSCK_MSG_BAD_TYPE ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_OBJECT ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_TAG ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_TAGGER_ENTRY ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_TAG_ENTRY ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_TAG_OBJECT ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_TYPE ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_TYPE_ENTRY ; 
 int /*<<< orphan*/  FSCK_MSG_TAG_OBJECT_NOT_TAG ; 
 int OBJ_TAG ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ check_refname_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fsck_ident (char const**,TYPE_1__*,struct fsck_options*) ; 
 scalar_t__ parse_oid_hex (char const*,struct object_id*,char const**) ; 
 char* read_object_file (int /*<<< orphan*/ *,int*,unsigned long*) ; 
 int report (struct fsck_options*,TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ type_from_string_gently (char const*,int,int) ; 
 int /*<<< orphan*/  type_name (int) ; 
 int verify_headers (char const*,unsigned long,TYPE_1__*,struct fsck_options*) ; 

__attribute__((used)) static int fsck_tag_buffer(struct tag *tag, const char *data,
	unsigned long size, struct fsck_options *options)
{
	struct object_id oid;
	int ret = 0;
	const char *buffer;
	char *to_free = NULL, *eol;
	struct strbuf sb = STRBUF_INIT;
	const char *p;

	if (data)
		buffer = data;
	else {
		enum object_type type;

		buffer = to_free =
			read_object_file(&tag->object.oid, &type, &size);
		if (!buffer)
			return report(options, &tag->object,
				FSCK_MSG_MISSING_TAG_OBJECT,
				"cannot read tag object");

		if (type != OBJ_TAG) {
			ret = report(options, &tag->object,
				FSCK_MSG_TAG_OBJECT_NOT_TAG,
				"expected tag got %s",
			    type_name(type));
			goto done;
		}
	}

	ret = verify_headers(buffer, size, &tag->object, options);
	if (ret)
		goto done;

	if (!skip_prefix(buffer, "object ", &buffer)) {
		ret = report(options, &tag->object, FSCK_MSG_MISSING_OBJECT, "invalid format - expected 'object' line");
		goto done;
	}
	if (parse_oid_hex(buffer, &oid, &p) || *p != '\n') {
		ret = report(options, &tag->object, FSCK_MSG_BAD_OBJECT_SHA1, "invalid 'object' line format - bad sha1");
		if (ret)
			goto done;
	}
	buffer = p + 1;

	if (!skip_prefix(buffer, "type ", &buffer)) {
		ret = report(options, &tag->object, FSCK_MSG_MISSING_TYPE_ENTRY, "invalid format - expected 'type' line");
		goto done;
	}
	eol = strchr(buffer, '\n');
	if (!eol) {
		ret = report(options, &tag->object, FSCK_MSG_MISSING_TYPE, "invalid format - unexpected end after 'type' line");
		goto done;
	}
	if (type_from_string_gently(buffer, eol - buffer, 1) < 0)
		ret = report(options, &tag->object, FSCK_MSG_BAD_TYPE, "invalid 'type' value");
	if (ret)
		goto done;
	buffer = eol + 1;

	if (!skip_prefix(buffer, "tag ", &buffer)) {
		ret = report(options, &tag->object, FSCK_MSG_MISSING_TAG_ENTRY, "invalid format - expected 'tag' line");
		goto done;
	}
	eol = strchr(buffer, '\n');
	if (!eol) {
		ret = report(options, &tag->object, FSCK_MSG_MISSING_TAG, "invalid format - unexpected end after 'type' line");
		goto done;
	}
	strbuf_addf(&sb, "refs/tags/%.*s", (int)(eol - buffer), buffer);
	if (check_refname_format(sb.buf, 0)) {
		ret = report(options, &tag->object, FSCK_MSG_BAD_TAG_NAME,
			   "invalid 'tag' name: %.*s",
			   (int)(eol - buffer), buffer);
		if (ret)
			goto done;
	}
	buffer = eol + 1;

	if (!skip_prefix(buffer, "tagger ", &buffer)) {
		/* early tags do not contain 'tagger' lines; warn only */
		ret = report(options, &tag->object, FSCK_MSG_MISSING_TAGGER_ENTRY, "invalid format - expected 'tagger' line");
		if (ret)
			goto done;
	}
	else
		ret = fsck_ident(&buffer, &tag->object, options);

done:
	strbuf_release(&sb);
	free(to_free);
	return ret;
}