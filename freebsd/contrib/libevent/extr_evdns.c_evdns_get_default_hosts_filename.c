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

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_SYSTEM ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  SHGetSpecialFolderPathA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,size_t,char*,char*,char const*) ; 
 char* mm_malloc (size_t) ; 
 char* mm_strdup (char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
evdns_get_default_hosts_filename(void)
{
#ifdef _WIN32
	/* Windows is a little coy about where it puts its configuration
	 * files.  Sure, they're _usually_ in C:\windows\system32, but
	 * there's no reason in principle they couldn't be in
	 * W:\hoboken chicken emergency\
	 */
	char path[MAX_PATH+1];
	static const char hostfile[] = "\\drivers\\etc\\hosts";
	char *path_out;
	size_t len_out;

	if (! SHGetSpecialFolderPathA(NULL, path, CSIDL_SYSTEM, 0))
		return NULL;
	len_out = strlen(path)+strlen(hostfile)+1;
	path_out = mm_malloc(len_out);
	evutil_snprintf(path_out, len_out, "%s%s", path, hostfile);
	return path_out;
#else
	return mm_strdup("/etc/hosts");
#endif
}