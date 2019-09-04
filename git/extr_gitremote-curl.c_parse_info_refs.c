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
struct ref {struct ref* next; int /*<<< orphan*/  old_oid; } ;
struct discovery {char* buf; int len; } ;
struct TYPE_4__ {int hexsz; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct ref* alloc_ref (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ref*) ; 
 int /*<<< orphan*/  get_oid_hex (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_fetch_ref (int /*<<< orphan*/ ,struct ref*) ; 
 int /*<<< orphan*/  resolve_remote_symref (struct ref*,struct ref*) ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  transport_anonymize_url (int /*<<< orphan*/ ) ; 
 TYPE_1__ url ; 

__attribute__((used)) static struct ref *parse_info_refs(struct discovery *heads)
{
	char *data, *start, *mid;
	char *ref_name;
	int i = 0;

	struct ref *refs = NULL;
	struct ref *ref = NULL;
	struct ref *last_ref = NULL;

	data = heads->buf;
	start = NULL;
	mid = data;
	while (i < heads->len) {
		if (!start) {
			start = &data[i];
		}
		if (data[i] == '\t')
			mid = &data[i];
		if (data[i] == '\n') {
			if (mid - start != the_hash_algo->hexsz)
				die(_("%sinfo/refs not valid: is this a git repository?"),
				    transport_anonymize_url(url.buf));
			data[i] = 0;
			ref_name = mid + 1;
			ref = alloc_ref(ref_name);
			get_oid_hex(start, &ref->old_oid);
			if (!refs)
				refs = ref;
			if (last_ref)
				last_ref->next = ref;
			last_ref = ref;
			start = NULL;
		}
		i++;
	}

	ref = alloc_ref("HEAD");
	if (!http_fetch_ref(url.buf, ref) &&
	    !resolve_remote_symref(ref, refs)) {
		ref->next = refs;
		refs = ref;
	} else {
		free(ref);
	}

	return refs;
}