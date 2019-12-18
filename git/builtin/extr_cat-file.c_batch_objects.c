#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct oidset {int dummy; } ;
struct oid_array {struct oidset* seen; struct strbuf* scratch; struct expand_data* expand; struct batch_options* opt; } ;
struct object_info {int dummy; } ;
struct object_cb_data {struct oidset* seen; struct strbuf* scratch; struct expand_data* expand; struct batch_options* opt; } ;
struct TYPE_2__ {int /*<<< orphan*/ * typep; } ;
struct expand_data {int mark_query; int split_on_whitespace; int skip_object_info; char* rest; int /*<<< orphan*/  type; TYPE_1__ info; } ;
struct batch_options {char* format; scalar_t__ unordered; scalar_t__ all_objects; scalar_t__ print_contents; scalar_t__ cmdmode; } ;
typedef  int /*<<< orphan*/  empty ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  FOR_EACH_OBJECT_PACK_ORDER ; 
 struct object_info OBJECT_INFO_INIT ; 
 struct oidset OIDSET_INIT ; 
 struct oid_array OID_ARRAY_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  batch_object_cb ; 
 int /*<<< orphan*/  batch_one_object (int /*<<< orphan*/ ,struct strbuf*,struct batch_options*,struct expand_data*) ; 
 int /*<<< orphan*/  batch_unordered_loose ; 
 int /*<<< orphan*/  batch_unordered_packed ; 
 int /*<<< orphan*/  collect_loose_object ; 
 int /*<<< orphan*/  collect_packed_object ; 
 int /*<<< orphan*/  expand_format ; 
 int /*<<< orphan*/  for_each_loose_object (int /*<<< orphan*/ ,struct oid_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_packed_object (int /*<<< orphan*/ ,struct oid_array*,int /*<<< orphan*/ ) ; 
 scalar_t__ has_promisor_remote () ; 
 int /*<<< orphan*/  memcmp (TYPE_1__*,struct object_info*,int) ; 
 int /*<<< orphan*/  memset (struct expand_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_array_clear (struct oid_array*) ; 
 int /*<<< orphan*/  oid_array_for_each_unique (struct oid_array*,int /*<<< orphan*/ ,struct oid_array*) ; 
 int /*<<< orphan*/  oidset_clear (struct oidset*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strbuf_expand (struct strbuf*,char*,int /*<<< orphan*/ ,struct expand_data*) ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strchr (char*,char) ; 
 char* strpbrk (int /*<<< orphan*/ ,char*) ; 
 int warn_on_object_refname_ambiguity ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static int batch_objects(struct batch_options *opt)
{
	struct strbuf input = STRBUF_INIT;
	struct strbuf output = STRBUF_INIT;
	struct expand_data data;
	int save_warning;
	int retval = 0;

	if (!opt->format)
		opt->format = "%(objectname) %(objecttype) %(objectsize)";

	/*
	 * Expand once with our special mark_query flag, which will prime the
	 * object_info to be handed to oid_object_info_extended for each
	 * object.
	 */
	memset(&data, 0, sizeof(data));
	data.mark_query = 1;
	strbuf_expand(&output, opt->format, expand_format, &data);
	data.mark_query = 0;
	strbuf_release(&output);
	if (opt->cmdmode)
		data.split_on_whitespace = 1;

	if (opt->all_objects) {
		struct object_info empty = OBJECT_INFO_INIT;
		if (!memcmp(&data.info, &empty, sizeof(empty)))
			data.skip_object_info = 1;
	}

	/*
	 * If we are printing out the object, then always fill in the type,
	 * since we will want to decide whether or not to stream.
	 */
	if (opt->print_contents)
		data.info.typep = &data.type;

	if (opt->all_objects) {
		struct object_cb_data cb;

		if (has_promisor_remote())
			warning("This repository uses promisor remotes. Some objects may not be loaded.");

		cb.opt = opt;
		cb.expand = &data;
		cb.scratch = &output;

		if (opt->unordered) {
			struct oidset seen = OIDSET_INIT;

			cb.seen = &seen;

			for_each_loose_object(batch_unordered_loose, &cb, 0);
			for_each_packed_object(batch_unordered_packed, &cb,
					       FOR_EACH_OBJECT_PACK_ORDER);

			oidset_clear(&seen);
		} else {
			struct oid_array sa = OID_ARRAY_INIT;

			for_each_loose_object(collect_loose_object, &sa, 0);
			for_each_packed_object(collect_packed_object, &sa, 0);

			oid_array_for_each_unique(&sa, batch_object_cb, &cb);

			oid_array_clear(&sa);
		}

		strbuf_release(&output);
		return 0;
	}

	/*
	 * We are going to call get_sha1 on a potentially very large number of
	 * objects. In most large cases, these will be actual object sha1s. The
	 * cost to double-check that each one is not also a ref (just so we can
	 * warn) ends up dwarfing the actual cost of the object lookups
	 * themselves. We can work around it by just turning off the warning.
	 */
	save_warning = warn_on_object_refname_ambiguity;
	warn_on_object_refname_ambiguity = 0;

	while (strbuf_getline(&input, stdin) != EOF) {
		if (data.split_on_whitespace) {
			/*
			 * Split at first whitespace, tying off the beginning
			 * of the string and saving the remainder (or NULL) in
			 * data.rest.
			 */
			char *p = strpbrk(input.buf, " \t");
			if (p) {
				while (*p && strchr(" \t", *p))
					*p++ = '\0';
			}
			data.rest = p;
		}

		batch_one_object(input.buf, &output, opt, &data);
	}

	strbuf_release(&input);
	strbuf_release(&output);
	warn_on_object_refname_ambiguity = save_warning;
	return retval;
}