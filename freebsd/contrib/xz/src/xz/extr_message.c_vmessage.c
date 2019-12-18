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
typedef  int /*<<< orphan*/  va_list ;
typedef  enum message_verbosity { ____Placeholder_message_verbosity } message_verbosity ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 char* progname ; 
 int /*<<< orphan*/  progress_flush (int) ; 
 int /*<<< orphan*/  signals_block () ; 
 int /*<<< orphan*/  signals_unblock () ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmessage(enum message_verbosity v, const char *fmt, va_list ap)
{
	if (v <= verbosity) {
		signals_block();

		progress_flush(false);

		// TRANSLATORS: This is the program name in the beginning
		// of the line in messages. Usually it becomes "xz: ".
		// This is a translatable string because French needs
		// a space before a colon.
		fprintf(stderr, _("%s: "), progname);
		vfprintf(stderr, fmt, ap);
		fputc('\n', stderr);

		signals_unblock();
	}

	return;
}