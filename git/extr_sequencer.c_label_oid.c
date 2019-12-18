#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct string_entry {char const* string; TYPE_2__ entry; } ;
struct strbuf {char* buf; } ;
struct object_id {int dummy; } ;
struct labels_entry {char const* string; TYPE_2__ entry; } ;
struct label_state {int /*<<< orphan*/  commit2label; int /*<<< orphan*/  labels; struct strbuf buf; } ;
struct TYPE_4__ {size_t hexsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_STR (struct string_entry*,char const*,char const*) ; 
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  default_abbrev ; 
 int /*<<< orphan*/  find_unique_abbrev_r (char*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_oid_hex (char const*,struct object_id*) ; 
 int /*<<< orphan*/  hashmap_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_entry_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ hashmap_get_from_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  oid_to_hex_r (char*,struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 struct string_entry* oidmap_get (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  oidmap_put (int /*<<< orphan*/ *,struct string_entry*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strihash (char const*) ; 
 char const* string ; 
 int strlen (char const*) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static const char *label_oid(struct object_id *oid, const char *label,
			     struct label_state *state)
{
	struct labels_entry *labels_entry;
	struct string_entry *string_entry;
	struct object_id dummy;
	size_t len;
	int i;

	string_entry = oidmap_get(&state->commit2label, oid);
	if (string_entry)
		return string_entry->string;

	/*
	 * For "uninteresting" commits, i.e. commits that are not to be
	 * rebased, and which can therefore not be labeled, we use a unique
	 * abbreviation of the commit name. This is slightly more complicated
	 * than calling find_unique_abbrev() because we also need to make
	 * sure that the abbreviation does not conflict with any other
	 * label.
	 *
	 * We disallow "interesting" commits to be labeled by a string that
	 * is a valid full-length hash, to ensure that we always can find an
	 * abbreviation for any uninteresting commit's names that does not
	 * clash with any other label.
	 */
	if (!label) {
		char *p;

		strbuf_reset(&state->buf);
		strbuf_grow(&state->buf, GIT_MAX_HEXSZ);
		label = p = state->buf.buf;

		find_unique_abbrev_r(p, oid, default_abbrev);

		/*
		 * We may need to extend the abbreviated hash so that there is
		 * no conflicting label.
		 */
		if (hashmap_get_from_hash(&state->labels, strihash(p), p)) {
			size_t i = strlen(p) + 1;

			oid_to_hex_r(p, oid);
			for (; i < the_hash_algo->hexsz; i++) {
				char save = p[i];
				p[i] = '\0';
				if (!hashmap_get_from_hash(&state->labels,
							   strihash(p), p))
					break;
				p[i] = save;
			}
		}
	} else if (((len = strlen(label)) == the_hash_algo->hexsz &&
		    !get_oid_hex(label, &dummy)) ||
		   (len == 1 && *label == '#') ||
		   hashmap_get_from_hash(&state->labels,
					 strihash(label), label)) {
		/*
		 * If the label already exists, or if the label is a valid full
		 * OID, or the label is a '#' (which we use as a separator
		 * between merge heads and oneline), we append a dash and a
		 * number to make it unique.
		 */
		struct strbuf *buf = &state->buf;

		strbuf_reset(buf);
		strbuf_add(buf, label, len);

		for (i = 2; ; i++) {
			strbuf_setlen(buf, len);
			strbuf_addf(buf, "-%d", i);
			if (!hashmap_get_from_hash(&state->labels,
						   strihash(buf->buf),
						   buf->buf))
				break;
		}

		label = buf->buf;
	}

	FLEX_ALLOC_STR(labels_entry, label, label);
	hashmap_entry_init(&labels_entry->entry, strihash(label));
	hashmap_add(&state->labels, &labels_entry->entry);

	FLEX_ALLOC_STR(string_entry, string, label);
	oidcpy(&string_entry->entry.oid, oid);
	oidmap_put(&state->commit2label, string_entry);

	return string_entry->string;
}