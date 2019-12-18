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
struct executable {char const* x_path; int /*<<< orphan*/ * x_fp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct executable* calloc (int,int) ; 
 scalar_t__ caph_enter () ; 
 int /*<<< orphan*/ * checked_fopen (char const*,char*) ; 
 int /*<<< orphan*/  digest (struct executable*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  load (struct executable*) ; 
 int /*<<< orphan*/  parse (struct executable*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  receive_signature (struct executable*,int) ; 
 int /*<<< orphan*/  save (struct executable*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  send_digest (struct executable*,int) ; 
 int /*<<< orphan*/  show_certificate (struct executable*) ; 
 int /*<<< orphan*/  show_digest (struct executable*) ; 
 scalar_t__ signature_size (struct executable*) ; 
 int /*<<< orphan*/  update (struct executable*) ; 

int
child(const char *inpath, const char *outpath, int pipefd,
    bool Vflag, bool vflag)
{
	FILE *outfp = NULL, *infp = NULL;
	struct executable *x;

	infp = checked_fopen(inpath, "r");
	if (outpath != NULL)
		outfp = checked_fopen(outpath, "w");

	if (caph_enter() < 0)
		err(1, "cap_enter");

	x = calloc(1, sizeof(*x));
	if (x == NULL)
		err(1, "calloc");
	x->x_path = inpath;
	x->x_fp = infp;

	load(x);
	parse(x);
	if (Vflag) {
		if (signature_size(x) == 0)
			errx(1, "file not signed");

		printf("file contains signature\n");
		if (vflag) {
			digest(x);
			show_digest(x);
			show_certificate(x);
		}
	} else {
		if (signature_size(x) != 0)
			errx(1, "file already signed");

		digest(x);
		if (vflag)
			show_digest(x);
		send_digest(x, pipefd);
		receive_signature(x, pipefd);
		update(x);
		save(x, outfp, outpath);
	}

	return (0);
}