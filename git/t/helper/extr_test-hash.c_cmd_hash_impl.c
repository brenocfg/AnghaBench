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
struct git_hash_algo {int /*<<< orphan*/  rawsz; int /*<<< orphan*/  (* final_fn ) (unsigned char*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,char*,scalar_t__) ;int /*<<< orphan*/  (* init_fn ) (int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  git_hash_ctx ;

/* Variables and functions */
 int GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct git_hash_algo* hash_algos ; 
 int /*<<< orphan*/  hash_to_hex_algop (unsigned char*,struct git_hash_algo const*) ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ xread (int /*<<< orphan*/ ,char*,unsigned int) ; 

int cmd_hash_impl(int ac, const char **av, int algo)
{
	git_hash_ctx ctx;
	unsigned char hash[GIT_MAX_HEXSZ];
	unsigned bufsz = 8192;
	int binary = 0;
	char *buffer;
	const struct git_hash_algo *algop = &hash_algos[algo];

	if (ac == 2) {
		if (!strcmp(av[1], "-b"))
			binary = 1;
		else
			bufsz = strtoul(av[1], NULL, 10) * 1024 * 1024;
	}

	if (!bufsz)
		bufsz = 8192;

	while ((buffer = malloc(bufsz)) == NULL) {
		fprintf(stderr, "bufsz %u is too big, halving...\n", bufsz);
		bufsz /= 2;
		if (bufsz < 1024)
			die("OOPS");
	}

	algop->init_fn(&ctx);

	while (1) {
		ssize_t sz, this_sz;
		char *cp = buffer;
		unsigned room = bufsz;
		this_sz = 0;
		while (room) {
			sz = xread(0, cp, room);
			if (sz == 0)
				break;
			if (sz < 0)
				die_errno("test-hash");
			this_sz += sz;
			cp += sz;
			room -= sz;
		}
		if (this_sz == 0)
			break;
		algop->update_fn(&ctx, buffer, this_sz);
	}
	algop->final_fn(hash, &ctx);

	if (binary)
		fwrite(hash, 1, algop->rawsz, stdout);
	else
		puts(hash_to_hex_algop(hash, algop));
	exit(0);
}