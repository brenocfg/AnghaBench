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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cwarn (char*,char const*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  force ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 size_t fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  permission (char const*) ; 
 int /*<<< orphan*/  setfile (char const*,struct stat*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ unlink (char const*) ; 
 int /*<<< orphan*/ * zopen (char const*,char*,int) ; 

__attribute__((used)) static void
decompress(const char *in, const char *out, int bits)
{
	size_t nr;
	struct stat sb;
	FILE *ifp, *ofp;
	int exists, isreg, oreg;
	u_char buf[1024];

	exists = !stat(out, &sb);
	if (!force && exists && S_ISREG(sb.st_mode) && !permission(out))
		return;
	isreg = oreg = !exists || S_ISREG(sb.st_mode);

	ifp = ofp = NULL;
	if ((ifp = zopen(in, "r", bits)) == NULL) {
		cwarn("%s", in);
		return;
	}
	if (stat(in, &sb)) {
		cwarn("%s", in);
		goto err;
	}
	if (!S_ISREG(sb.st_mode))
		isreg = 0;

	/*
	 * Try to read the first few uncompressed bytes from the input file
	 * before blindly truncating the output file.
	 */
	if ((nr = fread(buf, 1, sizeof(buf), ifp)) == 0) {
		cwarn("%s", in);
		(void)fclose(ifp);
		return;
	}
	if ((ofp = fopen(out, "w")) == NULL ||
	    (nr != 0 && fwrite(buf, 1, nr, ofp) != nr)) {
		cwarn("%s", out);
		if (ofp)
			(void)fclose(ofp);
		(void)fclose(ifp);
		return;
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

	if (isreg) {
		setfile(out, &sb);

		if (unlink(in))
			cwarn("%s", in);
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