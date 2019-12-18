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
struct fingerprint_list {int dummy; } ;
struct fingerprint {int dummy; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (struct fingerprint_list*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct fingerprint_list*,struct fingerprint*,int /*<<< orphan*/ ) ; 
 struct fingerprint_list* calloc (int,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct fingerprint_list*) ; 
 struct fingerprint* load_fingerprint (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct fingerprint_list *
load_fingerprints(const char *path, int *count)
{
	DIR *d;
	struct dirent *ent;
	struct fingerprint *finger;
	struct fingerprint_list *fingerprints;

	*count = 0;

	fingerprints = calloc(1, sizeof(struct fingerprint_list));
	if (fingerprints == NULL)
		return (NULL);
	STAILQ_INIT(fingerprints);

	if ((d = opendir(path)) == NULL) {
		free(fingerprints);

		return (NULL);
	}

	while ((ent = readdir(d))) {
		if (strcmp(ent->d_name, ".") == 0 ||
		    strcmp(ent->d_name, "..") == 0)
			continue;
		finger = load_fingerprint(path, ent->d_name);
		if (finger != NULL) {
			STAILQ_INSERT_TAIL(fingerprints, finger, next);
			++(*count);
		}
	}

	closedir(d);

	return (fingerprints);
}