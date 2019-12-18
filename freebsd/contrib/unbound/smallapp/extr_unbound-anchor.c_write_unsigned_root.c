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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FlushFileBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ _get_osfhandle (int /*<<< orphan*/ ) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ verb ; 

__attribute__((used)) static void
write_unsigned_root(const char* root_anchor_file)
{
	FILE* out;
	time_t now = time(NULL);
	out = fopen(root_anchor_file, "w");
	if(!out) {
		if(verb) printf("%s: %s\n", root_anchor_file, strerror(errno));
		return;
	}
	if(fprintf(out, "; autotrust trust anchor file\n"
		";;REVOKED\n"
		";;id: . 1\n"
		"; This file was written by unbound-anchor on %s"
		"; It indicates that the root does not use DNSSEC\n"
		"; to restart DNSSEC overwrite this file with a\n"
		"; valid trustanchor or (empty-it and run unbound-anchor)\n"
		, ctime(&now)) < 0) {
		if(verb) printf("failed to write 'unsigned' to %s\n",
			root_anchor_file);
		if(verb && errno != 0) printf("%s\n", strerror(errno));
	}
	fflush(out);
#ifdef HAVE_FSYNC
	fsync(fileno(out));
#else
	FlushFileBuffers((HANDLE)_get_osfhandle(_fileno(out)));
#endif
	fclose(out);
}