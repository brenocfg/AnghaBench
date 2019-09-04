#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * output; int /*<<< orphan*/  getline; } ;
struct rerere_io_mem {TYPE_1__ io; int /*<<< orphan*/  input; } ;
struct rerere_io {int dummy; } ;
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {unsigned long size; scalar_t__ ptr; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ mmfile_t ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_3__ mmbuffer_t ;
typedef  int /*<<< orphan*/  io ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int ce_namelen (struct cache_entry const*) ; 
 int ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int handle_path (unsigned char*,struct rerere_io*,int) ; 
 int index_name_pos (struct index_state*,char const*,int) ; 
 int /*<<< orphan*/  ll_merge (TYPE_3__*,char const*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*,char*,TYPE_2__*,char*,struct index_state*,int /*<<< orphan*/ *) ; 
 int ll_merge_marker_size (struct index_state*,char const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (struct rerere_io_mem*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_object_file (int /*<<< orphan*/ *,int*,unsigned long*) ; 
 int /*<<< orphan*/  rerere_mem_getline ; 
 int /*<<< orphan*/  strbuf_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ xstrdup (char*) ; 

__attribute__((used)) static int handle_cache(struct index_state *istate,
			const char *path, unsigned char *hash, const char *output)
{
	mmfile_t mmfile[3] = {{NULL}};
	mmbuffer_t result = {NULL, 0};
	const struct cache_entry *ce;
	int pos, len, i, has_conflicts;
	struct rerere_io_mem io;
	int marker_size = ll_merge_marker_size(istate, path);

	/*
	 * Reproduce the conflicted merge in-core
	 */
	len = strlen(path);
	pos = index_name_pos(istate, path, len);
	if (0 <= pos)
		return -1;
	pos = -pos - 1;

	while (pos < istate->cache_nr) {
		enum object_type type;
		unsigned long size;

		ce = istate->cache[pos++];
		if (ce_namelen(ce) != len || memcmp(ce->name, path, len))
			break;
		i = ce_stage(ce) - 1;
		if (!mmfile[i].ptr) {
			mmfile[i].ptr = read_object_file(&ce->oid, &type,
							 &size);
			mmfile[i].size = size;
		}
	}
	for (i = 0; i < 3; i++)
		if (!mmfile[i].ptr && !mmfile[i].size)
			mmfile[i].ptr = xstrdup("");

	/*
	 * NEEDSWORK: handle conflicts from merges with
	 * merge.renormalize set, too?
	 */
	ll_merge(&result, path, &mmfile[0], NULL,
		 &mmfile[1], "ours",
		 &mmfile[2], "theirs",
		 istate, NULL);
	for (i = 0; i < 3; i++)
		free(mmfile[i].ptr);

	memset(&io, 0, sizeof(io));
	io.io.getline = rerere_mem_getline;
	if (output)
		io.io.output = fopen(output, "w");
	else
		io.io.output = NULL;
	strbuf_init(&io.input, 0);
	strbuf_attach(&io.input, result.ptr, result.size, result.size);

	/*
	 * Grab the conflict ID and optionally write the original
	 * contents with conflict markers out.
	 */
	has_conflicts = handle_path(hash, (struct rerere_io *)&io, marker_size);
	strbuf_release(&io.input);
	if (io.io.output)
		fclose(io.io.output);
	return has_conflicts;
}