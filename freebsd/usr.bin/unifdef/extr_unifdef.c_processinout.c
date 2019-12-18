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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  altered ; 
 char* astrcat (char const*,char*) ; 
 char* backext ; 
 int /*<<< orphan*/  err (int,char*,char const*,...) ; 
 void* fbinmode (int /*<<< orphan*/ ) ; 
 char const* filename ; 
 void* fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input ; 
 char const* linefile ; 
 int /*<<< orphan*/ * mktempmode (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * output ; 
 int /*<<< orphan*/  process () ; 
 scalar_t__ remove (char*) ; 
 scalar_t__ rename (char const*,char*) ; 
 scalar_t__ replace (char*,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* tempname ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
processinout(const char *ifn, const char *ofn)
{
	struct stat st;

	if (ifn == NULL || strcmp(ifn, "-") == 0) {
		filename = "[stdin]";
		linefile = NULL;
		input = fbinmode(stdin);
	} else {
		filename = ifn;
		linefile = ifn;
		input = fopen(ifn, "rb");
		if (input == NULL)
			err(2, "can't open %s", ifn);
	}
	if (strcmp(ofn, "-") == 0) {
		output = fbinmode(stdout);
		process();
		return;
	}
	if (stat(ofn, &st) < 0) {
		output = fopen(ofn, "wb");
		if (output == NULL)
			err(2, "can't create %s", ofn);
		process();
		return;
	}

	tempname = astrcat(ofn, ".XXXXXX");
	output = mktempmode(tempname, st.st_mode);
	if (output == NULL)
		err(2, "can't create %s", tempname);

	process();

	if (backext != NULL) {
		char *backname = astrcat(ofn, backext);
		if (rename(ofn, backname) < 0)
			err(2, "can't rename \"%s\" to \"%s\"", ofn, backname);
		free(backname);
	}
	/* leave file unmodified if unifdef made no changes */
	if (!altered && backext == NULL) {
		if (remove(tempname) < 0)
			warn("can't remove \"%s\"", tempname);
	} else if (replace(tempname, ofn) < 0)
		err(2, "can't rename \"%s\" to \"%s\"", tempname, ofn);
	free(tempname);
	tempname = NULL;
}