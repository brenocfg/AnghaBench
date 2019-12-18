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
struct dumpdates {int /*<<< orphan*/  dd_ddate; int /*<<< orphan*/  dd_level; int /*<<< orphan*/  dd_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DUMPFMTLEN ; 
 char* DUMPOUTFMT ; 
 int /*<<< orphan*/  ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dumpdates ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quit (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dumprecout(FILE *file, const struct dumpdates *what)
{

	if (strlen(what->dd_name) > DUMPFMTLEN)
		quit("Name '%s' exceeds DUMPFMTLEN (%d) bytes\n",
		    what->dd_name, DUMPFMTLEN);
	if (fprintf(file, DUMPOUTFMT, DUMPFMTLEN, what->dd_name,
	      what->dd_level, ctime(&what->dd_ddate)) < 0)
		quit("%s: %s\n", dumpdates, strerror(errno));
}