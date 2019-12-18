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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int type; char* s; unsigned int len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  AP_FILE 129 
#define  AP_STRING 128 
 scalar_t__ EIO ; 
 TYPE_1__* appends ; 
 unsigned int appendx ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 unsigned int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  outfname ; 
 unsigned int sdone ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void
flush_appends(void)
{
	FILE *f;
	unsigned int count, idx;
	char buf[8 * 1024];

	for (idx = 0; idx < appendx; idx++)
		switch (appends[idx].type) {
		case AP_STRING:
			fwrite(appends[idx].s, sizeof(char), appends[idx].len,
			    outfile);
			break;
		case AP_FILE:
			/*
			 * Read files probably shouldn't be cached.  Since
			 * it's not an error to read a non-existent file,
			 * it's possible that another program is interacting
			 * with the sed script through the filesystem.  It
			 * would be truly bizarre, but possible.  It's probably
			 * not that big a performance win, anyhow.
			 */
			if ((f = fopen(appends[idx].s, "r")) == NULL)
				break;
			while ((count = fread(buf, sizeof(char), sizeof(buf), f)))
				(void)fwrite(buf, sizeof(char), count, outfile);
			(void)fclose(f);
			break;
		}
	if (ferror(outfile))
		errx(1, "%s: %s", outfname, strerror(errno ? errno : EIO));
	appendx = sdone = 0;
}