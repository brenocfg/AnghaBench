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
struct smbmount {int /*<<< orphan*/  sm_share; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int LOOKUP ; 
 scalar_t__ SMB_DIALECT (int /*<<< orphan*/ ) ; 
 scalar_t__ SMB_DIALECT_LANMAN2_0 ; 
 int /*<<< orphan*/  SSTOVC (int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char const) ; 

__attribute__((used)) static int
smbfs_pathcheck(struct smbmount *smp, const char *name, int nmlen, int nameiop)
{
	static const char *badchars = "*/:<>?";
	static const char *badchars83 = " +|,[]=;";
	const char *cp;
	int i, error;

	/*
	 * Backslash characters, being a path delimiter, are prohibited
	 * within a path component even for LOOKUP operations.
	 */
	if (strchr(name, '\\') != NULL)
		return ENOENT;

	if (nameiop == LOOKUP)
		return 0;
	error = ENOENT;
	if (SMB_DIALECT(SSTOVC(smp->sm_share)) < SMB_DIALECT_LANMAN2_0) {
		/*
		 * Name should conform 8.3 format
		 */
		if (nmlen > 12)
			return ENAMETOOLONG;
		cp = strchr(name, '.');
		if (cp == NULL)
			return error;
		if (cp == name || (cp - name) > 8)
			return error;
		cp = strchr(cp + 1, '.');
		if (cp != NULL)
			return error;
		for (cp = name, i = 0; i < nmlen; i++, cp++)
			if (strchr(badchars83, *cp) != NULL)
				return error;
	}
	for (cp = name, i = 0; i < nmlen; i++, cp++)
		if (strchr(badchars, *cp) != NULL)
			return error;
	return 0;
}