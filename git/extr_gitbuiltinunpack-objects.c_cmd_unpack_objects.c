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
struct pack_header {void* hdr_entries; void* hdr_version; void* hdr_signature; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct TYPE_2__ {int /*<<< orphan*/  rawsz; int /*<<< orphan*/  (* final_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* init_fn ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PACK_SIGNATURE ; 
 char* _ (char*) ; 
 scalar_t__ buffer ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int dry_run ; 
 int /*<<< orphan*/  fill (int /*<<< orphan*/ ) ; 
 scalar_t__ fsck_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsck_options ; 
 int /*<<< orphan*/  fsck_set_msg_types (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int has_errors ; 
 int /*<<< orphan*/  hasheq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isatty (int) ; 
 int len ; 
 int /*<<< orphan*/  max_input_size ; 
 scalar_t__ offset ; 
 int quiet ; 
 scalar_t__ read_replace_refs ; 
 int recover ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strict ; 
 int /*<<< orphan*/  strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  strtoumax (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  unpack_all () ; 
 int /*<<< orphan*/  unpack_usage ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_rest () ; 
 int xwrite (int,scalar_t__,int) ; 

int cmd_unpack_objects(int argc, const char **argv, const char *prefix)
{
	int i;
	struct object_id oid;

	read_replace_refs = 0;

	git_config(git_default_config, NULL);

	quiet = !isatty(2);

	for (i = 1 ; i < argc; i++) {
		const char *arg = argv[i];

		if (*arg == '-') {
			if (!strcmp(arg, "-n")) {
				dry_run = 1;
				continue;
			}
			if (!strcmp(arg, "-q")) {
				quiet = 1;
				continue;
			}
			if (!strcmp(arg, "-r")) {
				recover = 1;
				continue;
			}
			if (!strcmp(arg, "--strict")) {
				strict = 1;
				continue;
			}
			if (skip_prefix(arg, "--strict=", &arg)) {
				strict = 1;
				fsck_set_msg_types(&fsck_options, arg);
				continue;
			}
			if (starts_with(arg, "--pack_header=")) {
				struct pack_header *hdr;
				char *c;

				hdr = (struct pack_header *)buffer;
				hdr->hdr_signature = htonl(PACK_SIGNATURE);
				hdr->hdr_version = htonl(strtoul(arg + 14, &c, 10));
				if (*c != ',')
					die("bad %s", arg);
				hdr->hdr_entries = htonl(strtoul(c + 1, &c, 10));
				if (*c)
					die("bad %s", arg);
				len = sizeof(*hdr);
				continue;
			}
			if (skip_prefix(arg, "--max-input-size=", &arg)) {
				max_input_size = strtoumax(arg, NULL, 10);
				continue;
			}
			usage(unpack_usage);
		}

		/* We don't take any non-flag arguments now.. Maybe some day */
		usage(unpack_usage);
	}
	the_hash_algo->init_fn(&ctx);
	unpack_all();
	the_hash_algo->update_fn(&ctx, buffer, offset);
	the_hash_algo->final_fn(oid.hash, &ctx);
	if (strict) {
		write_rest();
		if (fsck_finish(&fsck_options))
			die(_("fsck error in pack objects"));
	}
	if (!hasheq(fill(the_hash_algo->rawsz), oid.hash))
		die("final sha1 did not match");
	use(the_hash_algo->rawsz);

	/* Write the last part of the buffer to stdout */
	while (len) {
		int ret = xwrite(1, buffer + offset, len);
		if (ret <= 0)
			break;
		len -= ret;
		offset += ret;
	}

	/* All done */
	return has_errors;
}