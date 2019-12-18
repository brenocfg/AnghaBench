#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_2__ {char const* suffix; } ;

/* Variables and functions */
 int COMPRESS_TYPES ; 
 int MAXPATHLEN ; 
 TYPE_1__* compress_type ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static const char *
get_logfile_suffix(const char *logfile)
{
	struct stat st;
	char zfile[MAXPATHLEN];
	int c;

	for (c = 0; c < COMPRESS_TYPES; c++) {
		(void) strlcpy(zfile, logfile, MAXPATHLEN);
		(void) strlcat(zfile, compress_type[c].suffix, MAXPATHLEN);
		if (lstat(zfile, &st) == 0)
			return (compress_type[c].suffix);
	}
	return (NULL);
}