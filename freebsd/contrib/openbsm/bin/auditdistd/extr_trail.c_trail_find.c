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
struct trail {scalar_t__ tr_magic; int /*<<< orphan*/  tr_filename; int /*<<< orphan*/  tr_dirfp; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 scalar_t__ HALF_LEN ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
 scalar_t__ TRAIL_MAGIC ; 
 struct dirent* readdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewinddir (int /*<<< orphan*/ ) ; 
 int strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int trail_is_not_terminated (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
trail_find(struct trail *trail)
{
	struct dirent *dp;

	PJDLOG_ASSERT(trail->tr_magic == TRAIL_MAGIC);
	PJDLOG_ASSERT(trail_is_not_terminated(trail->tr_filename));

	rewinddir(trail->tr_dirfp);
	while ((dp = readdir(trail->tr_dirfp)) != NULL) {
		if (strncmp(dp->d_name, trail->tr_filename, HALF_LEN + 1) == 0)
			break;
	}
	if (dp == NULL)
		return (false);
	PJDLOG_VERIFY(strlcpy(trail->tr_filename, dp->d_name,
	    sizeof(trail->tr_filename)) < sizeof(trail->tr_filename));
	return (true);
}