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
struct url {int /*<<< orphan*/  offset; int /*<<< orphan*/  doc; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CHECK_FLAG (char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fetch_syserr () ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

FILE *
fetchPutFile(struct url *u, const char *flags)
{
	FILE *f;

	if (CHECK_FLAG('a'))
		f = fopen(u->doc, "ae");
	else
		f = fopen(u->doc, "w+e");

	if (f == NULL) {
		fetch_syserr();
		return (NULL);
	}

	if (u->offset && fseeko(f, u->offset, SEEK_SET) == -1) {
		fclose(f);
		fetch_syserr();
		return (NULL);
	}

	return (f);
}