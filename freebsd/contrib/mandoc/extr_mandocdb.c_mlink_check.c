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
struct str {int mask; } ;
struct mpage {scalar_t__ form; int /*<<< orphan*/  arch; int /*<<< orphan*/  sec; } ;
struct mlink {int /*<<< orphan*/  file; int /*<<< orphan*/  name; int /*<<< orphan*/  arch; int /*<<< orphan*/  dsec; } ;

/* Variables and functions */
 scalar_t__ FORM_CAT ; 
 scalar_t__ FORM_SRC ; 
 int NAME_TITLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  names ; 
 struct str* ohash_find (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int ohash_qlookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  say (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlink_check(struct mpage *mpage, struct mlink *mlink)
{
	struct str	*str;
	unsigned int	 slot;

	/*
	 * Check whether the manual section given in a file
	 * agrees with the directory where the file is located.
	 * Some manuals have suffixes like (3p) on their
	 * section number either inside the file or in the
	 * directory name, some are linked into more than one
	 * section, like encrypt(1) = makekey(8).
	 */

	if (FORM_SRC == mpage->form &&
	    strcasecmp(mpage->sec, mlink->dsec))
		say(mlink->file, "Section \"%s\" manual in %s directory",
		    mpage->sec, mlink->dsec);

	/*
	 * Manual page directories exist for each kernel
	 * architecture as returned by machine(1).
	 * However, many manuals only depend on the
	 * application architecture as returned by arch(1).
	 * For example, some (2/ARM) manuals are shared
	 * across the "armish" and "zaurus" kernel
	 * architectures.
	 * A few manuals are even shared across completely
	 * different architectures, for example fdformat(1)
	 * on amd64, i386, and sparc64.
	 */

	if (strcasecmp(mpage->arch, mlink->arch))
		say(mlink->file, "Architecture \"%s\" manual in "
		    "\"%s\" directory", mpage->arch, mlink->arch);

	/*
	 * XXX
	 * parse_cat() doesn't set NAME_TITLE yet.
	 */

	if (FORM_CAT == mpage->form)
		return;

	/*
	 * Check whether this mlink
	 * appears as a name in the NAME section.
	 */

	slot = ohash_qlookup(&names, mlink->name);
	str = ohash_find(&names, slot);
	assert(NULL != str);
	if ( ! (NAME_TITLE & str->mask))
		say(mlink->file, "Name missing in NAME section");
}