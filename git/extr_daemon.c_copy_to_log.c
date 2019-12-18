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
struct strbuf {int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  logerror (char*,...) ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_to_log(int fd)
{
	struct strbuf line = STRBUF_INIT;
	FILE *fp;

	fp = fdopen(fd, "r");
	if (fp == NULL) {
		logerror("fdopen of error channel failed");
		close(fd);
		return;
	}

	while (strbuf_getline_lf(&line, fp) != EOF) {
		logerror("%s", line.buf);
		strbuf_setlen(&line, 0);
	}

	strbuf_release(&line);
	fclose(fp);
}