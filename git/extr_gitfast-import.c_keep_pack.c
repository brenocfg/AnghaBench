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
struct TYPE_2__ {char const* pack_name; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 scalar_t__ finalize_object_file (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int odb_pack_keep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odb_pack_name (struct strbuf*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* pack_data ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  write_or_die (int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *keep_pack(const char *curr_index_name)
{
	static const char *keep_msg = "fast-import";
	struct strbuf name = STRBUF_INIT;
	int keep_fd;

	odb_pack_name(&name, pack_data->hash, "keep");
	keep_fd = odb_pack_keep(name.buf);
	if (keep_fd < 0)
		die_errno("cannot create keep file");
	write_or_die(keep_fd, keep_msg, strlen(keep_msg));
	if (close(keep_fd))
		die_errno("failed to write keep file");

	odb_pack_name(&name, pack_data->hash, "pack");
	if (finalize_object_file(pack_data->pack_name, name.buf))
		die("cannot store pack file");

	odb_pack_name(&name, pack_data->hash, "idx");
	if (finalize_object_file(curr_index_name, name.buf))
		die("cannot store index file");
	free((void *)curr_index_name);
	return strbuf_detach(&name, NULL);
}