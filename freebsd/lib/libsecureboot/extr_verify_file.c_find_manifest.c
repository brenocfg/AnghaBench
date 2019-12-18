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
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINTF (int,char*) ; 
 char* MANIFEST_SKIP ; 
 char* MANIFEST_SKIP_ALWAYS ; 
 int MAXPATHLEN ; 
 int VE_FINGERPRINT_NONE ; 
 int /*<<< orphan*/  free (char*) ; 
 int load_manifest (char*,char*,char*,struct stat*) ; 
 char** manifest_names ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
find_manifest(const char *name)
{
	struct stat st;
	char buf[MAXPATHLEN];
	char *prefix;
	char *skip;
	const char **tp;
	int rc;

	strncpy(buf, name, MAXPATHLEN - 1);
	if (!(prefix = strrchr(buf, '/')))
		return (-1);
	*prefix = '\0';
	prefix = strdup(buf);
	rc = VE_FINGERPRINT_NONE;
	for (tp = manifest_names; *tp; tp++) {
		snprintf(buf, sizeof(buf), "%s/%s", prefix, *tp);
		DEBUG_PRINTF(5, ("looking for %s\n", buf));
		if (stat(buf, &st) == 0 && st.st_size > 0) {
#ifdef MANIFEST_SKIP_ALWAYS		/* very unlikely */
			skip = MANIFEST_SKIP_ALWAYS;
#else
#ifdef MANIFEST_SKIP			/* rare */
			if (*tp[0] == '.') {
				skip = MANIFEST_SKIP;
			} else
#endif
				skip = NULL;
#endif
			rc = load_manifest(buf, skip ? prefix : NULL,
			    skip, &st);
			break;
		}
	}
	free(prefix);
	return (rc);
}