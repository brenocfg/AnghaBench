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
typedef  scalar_t__ uintmax_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__* zipped; } ;
typedef  TYPE_1__ suffixes_t ;
struct stat {int st_size; int st_nlink; scalar_t__ st_mtime; } ;
typedef  int off_t ;
struct TYPE_5__ {char* ziplen; int /*<<< orphan*/  zipped; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  basename (char*) ; 
 scalar_t__ cflag ; 
 scalar_t__ check_outfile (char*) ; 
 TYPE_1__* check_suffix (char*,int /*<<< orphan*/ ) ; 
 int close (int) ; 
 int /*<<< orphan*/  copymodes (int,struct stat*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ fflag ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int gz_compress (int,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infile_set (char*,int) ; 
 int /*<<< orphan*/  maybe_warn (char*,...) ; 
 int /*<<< orphan*/  maybe_warnx (char*,char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,char*) ; 
 int open (char*,int,...) ; 
 char* remove_file ; 
 scalar_t__ snprintf (char*,size_t,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 TYPE_2__* suffixes ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  unlink_input (char*,struct stat*) ; 

__attribute__((used)) static off_t
file_compress(char *file, char *outfile, size_t outsize)
{
	int in;
	int out;
	off_t size, in_size;
#ifndef SMALL
	struct stat isb, osb;
	const suffixes_t *suff;
#endif

	in = open(file, O_RDONLY);
	if (in == -1) {
		maybe_warn("can't open %s", file);
		return (-1);
	}

#ifndef SMALL
	if (fstat(in, &isb) != 0) {
		maybe_warn("couldn't stat: %s", file);
		close(in);
		return (-1);
	}
#endif

#ifndef SMALL
	if (fstat(in, &isb) != 0) {
		close(in);
		maybe_warn("can't stat %s", file);
		return -1;
	}
	infile_set(file, isb.st_size);
#endif

	if (cflag == 0) {
#ifndef SMALL
		if (isb.st_nlink > 1 && fflag == 0) {
			maybe_warnx("%s has %ju other link%s -- "
				    "skipping", file,
				    (uintmax_t)isb.st_nlink - 1,
				    isb.st_nlink == 1 ? "" : "s");
			close(in);
			return -1;
		}

		if (fflag == 0 && (suff = check_suffix(file, 0)) &&
		    suff->zipped[0] != 0) {
			maybe_warnx("%s already has %s suffix -- unchanged",
			    file, suff->zipped);
			close(in);
			return (-1);
		}
#endif

		/* Add (usually) .gz to filename */
		if ((size_t)snprintf(outfile, outsize, "%s%s",
		    file, suffixes[0].zipped) >= outsize)
			memcpy(outfile + outsize - suffixes[0].ziplen - 1,
			    suffixes[0].zipped, suffixes[0].ziplen + 1);

#ifndef SMALL
		if (check_outfile(outfile) == 0) {
			close(in);
			return (-1);
		}
#endif
	}

	if (cflag == 0) {
		out = open(outfile, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (out == -1) {
			maybe_warn("could not create output: %s", outfile);
			fclose(stdin);
			return (-1);
		}
#ifndef SMALL
		remove_file = outfile;
#endif
	} else
		out = STDOUT_FILENO;

	in_size = gz_compress(in, out, &size, basename(file), (uint32_t)isb.st_mtime);

	(void)close(in);

	/*
	 * If there was an error, in_size will be -1.
	 * If we compressed to stdout, just return the size.
	 * Otherwise stat the file and check it is the correct size.
	 * We only blow away the file if we can stat the output and it
	 * has the expected size.
	 */
	if (cflag != 0)
		return in_size == -1 ? -1 : size;

#ifndef SMALL
	if (fstat(out, &osb) != 0) {
		maybe_warn("couldn't stat: %s", outfile);
		goto bad_outfile;
	}

	if (osb.st_size != size) {
		maybe_warnx("output file: %s wrong size (%ju != %ju), deleting",
		    outfile, (uintmax_t)osb.st_size, (uintmax_t)size);
		goto bad_outfile;
	}

	copymodes(out, &isb, outfile);
	remove_file = NULL;
#endif
	if (close(out) == -1)
		maybe_warn("couldn't close output");

	/* output is good, ok to delete input */
	unlink_input(file, &isb);
	return (size);

#ifndef SMALL
    bad_outfile:
	if (close(out) == -1)
		maybe_warn("couldn't close output");

	maybe_warnx("leaving original %s", file);
	unlink(outfile);
	return (size);
#endif
}