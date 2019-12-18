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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINTF (int,char*) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 char** signature_exts ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 unsigned char* verify_asc (char*,int) ; 
 unsigned char* verify_sig (char*,int) ; 

unsigned char *
verify_signed(const char *filename, int flags)
{
	struct stat st;
	char buf[MAXPATHLEN];
	const char **se;

	for (se = signature_exts; *se; se++) {
		snprintf(buf, sizeof(buf), "%s.%s", filename, *se);
		if (stat(buf, &st) < 0 || !S_ISREG(st.st_mode))
			continue;
		DEBUG_PRINTF(5, ("verify_signed: %s\n", buf));
#ifdef VE_OPENPGP_SUPPORT
		if (strncmp(*se, "asc", 3) == 0)
			return (verify_asc(buf, flags));
#endif
		return (verify_sig(buf, flags));
	}
	return (NULL);
}