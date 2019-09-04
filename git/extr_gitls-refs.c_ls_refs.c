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
struct repository {int dummy; } ;
struct packet_reader {char* line; } ;
struct ls_refs_data {int peel; int symrefs; int /*<<< orphan*/  prefixes; } ;
struct argv_array {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 scalar_t__ PACKET_READ_FLUSH ; 
 int /*<<< orphan*/  argv_array_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  for_each_namespaced_ref (int /*<<< orphan*/ ,struct ls_refs_data*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  head_ref_namespaced (int /*<<< orphan*/ ,struct ls_refs_data*) ; 
 int /*<<< orphan*/  ls_refs_config ; 
 int /*<<< orphan*/  memset (struct ls_refs_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  packet_flush (int) ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  send_ref ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

int ls_refs(struct repository *r, struct argv_array *keys,
	    struct packet_reader *request)
{
	struct ls_refs_data data;

	memset(&data, 0, sizeof(data));

	git_config(ls_refs_config, NULL);

	while (packet_reader_read(request) != PACKET_READ_FLUSH) {
		const char *arg = request->line;
		const char *out;

		if (!strcmp("peel", arg))
			data.peel = 1;
		else if (!strcmp("symrefs", arg))
			data.symrefs = 1;
		else if (skip_prefix(arg, "ref-prefix ", &out))
			argv_array_push(&data.prefixes, out);
	}

	head_ref_namespaced(send_ref, &data);
	for_each_namespaced_ref(send_ref, &data);
	packet_flush(1);
	argv_array_clear(&data.prefixes);
	return 0;
}