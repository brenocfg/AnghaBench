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
typedef  int /*<<< orphan*/  u_char ;
struct stat {float st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cwarn (char*,char const*) ; 
 int eval ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  force ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 size_t fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  permission (char const*) ; 
 int /*<<< orphan*/  setfile (char const*,struct stat*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ unlink (char const*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/ * zopen (char const*,char*,int) ; 

__attribute__((used)) static void
compress(const char *in, const char *out, int bits)
{
	size_t nr;
	struct stat isb, sb;
	FILE *ifp, *ofp;
	int exists, isreg, oreg;
	u_char buf[1024];

	exists = !stat(out, &sb);
	if (!force && exists && S_ISREG(sb.st_mode) && !permission(out))
		return;
	isreg = oreg = !exists || S_ISREG(sb.st_mode);

	ifp = ofp = NULL;
	if ((ifp = fopen(in, "r")) == NULL) {
		cwarn("%s", in);
		return;
	}
	if (stat(in, &isb)) {		/* DON'T FSTAT! */
		cwarn("%s", in);
		goto err;
	}
	if (!S_ISREG(isb.st_mode))
		isreg = 0;

	if ((ofp = zopen(out, "w", bits)) == NULL) {
		cwarn("%s", out);
		goto err;
	}
	while ((nr = fread(buf, 1, sizeof(buf), ifp)) != 0)
		if (fwrite(buf, 1, nr, ofp) != nr) {
			cwarn("%s", out);
			goto err;
		}

	if (ferror(ifp) || fclose(ifp)) {
		cwarn("%s", in);
		goto err;
	}
	ifp = NULL;

	if (fclose(ofp)) {
		cwarn("%s", out);
		goto err;
	}
	ofp = NULL;

	if (isreg) {
		if (stat(out, &sb)) {
			cwarn("%s", out);
			goto err;
		}

		if (!force && sb.st_size >= isb.st_size) {
			if (verbose)
		(void)fprintf(stderr, "%s: file would grow; left unmodified\n",
		    in);
			eval = 2;
			if (unlink(out))
				cwarn("%s", out);
			goto err;
		}

		setfile(out, &isb);

		if (unlink(in))
			cwarn("%s", in);

		if (verbose) {
			(void)fprintf(stderr, "%s: ", out);
			if (isb.st_size > sb.st_size)
				(void)fprintf(stderr, "%.0f%% compression\n",
				    ((float)sb.st_size / isb.st_size) * 100.0);
			else
				(void)fprintf(stderr, "%.0f%% expansion\n",
				    ((float)isb.st_size / sb.st_size) * 100.0);
		}
	}
	return;

err:	if (ofp) {
		if (oreg)
			(void)unlink(out);
		(void)fclose(ofp);
	}
	if (ifp)
		(void)fclose(ifp);
}