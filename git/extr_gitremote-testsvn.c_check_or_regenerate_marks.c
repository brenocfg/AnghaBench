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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_notes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_notes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marksfilename ; 
 int /*<<< orphan*/  notes_ref ; 
 int /*<<< orphan*/  regenerate_marks () ; 
 scalar_t__ starts_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int) ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/ * xfopen (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void check_or_regenerate_marks(int latestrev)
{
	FILE *marksfile;
	struct strbuf sb = STRBUF_INIT;
	struct strbuf line = STRBUF_INIT;
	int found = 0;

	if (latestrev < 1)
		return;

	init_notes(NULL, notes_ref, NULL, 0);
	marksfile = fopen(marksfilename, "r");
	if (!marksfile) {
		regenerate_marks();
		marksfile = xfopen(marksfilename, "r");
		fclose(marksfile);
	} else {
		strbuf_addf(&sb, ":%d ", latestrev);
		while (strbuf_getline_lf(&line, marksfile) != EOF) {
			if (starts_with(line.buf, sb.buf)) {
				found++;
				break;
			}
		}
		fclose(marksfile);
		if (!found)
			regenerate_marks();
	}
	free_notes(NULL);
	strbuf_release(&sb);
	strbuf_release(&line);
}