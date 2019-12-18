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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_get_mem_data (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  BIO_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushFileBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ _get_osfhandle (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 int fwrite (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (scalar_t__) ; 
 scalar_t__ verb ; 

__attribute__((used)) static void
write_root_anchor(const char* root_anchor_file, BIO* ds)
{
	char* pp = NULL;
	int len;
	FILE* out;
	(void)BIO_seek(ds, 0);
	len = BIO_get_mem_data(ds, &pp);
	if(!len || !pp) {
		if(verb) printf("out of memory\n");
		return;
	}
	out = fopen(root_anchor_file, "w");
	if(!out) {
		if(verb) printf("%s: %s\n", root_anchor_file, strerror(errno));
		return;
	}
	if(fwrite(pp, (size_t)len, 1, out) != 1) {
		if(verb) printf("failed to write all data to %s\n",
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