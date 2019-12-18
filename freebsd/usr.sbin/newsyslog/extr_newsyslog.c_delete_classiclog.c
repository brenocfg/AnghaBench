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
typedef  int /*<<< orphan*/  zfile1 ;
typedef  int /*<<< orphan*/  file1 ;
struct TYPE_2__ {int /*<<< orphan*/  suffix; } ;

/* Variables and functions */
 int COMPRESS_TYPES ; 
 int MAXPATHLEN ; 
 TYPE_1__* compress_type ; 
 int /*<<< orphan*/  gen_classiclog_fname (char*,int,char const*,char const*,int) ; 
 scalar_t__ noaction ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
delete_classiclog(const char *archive_dir, const char *namepart, int numlog_c)
{
	char file1[MAXPATHLEN], zfile1[MAXPATHLEN];
	int c;

	gen_classiclog_fname(file1, sizeof(file1), archive_dir, namepart,
	    numlog_c);

	for (c = 0; c < COMPRESS_TYPES; c++) {
		(void) snprintf(zfile1, sizeof(zfile1), "%s%s", file1,
		    compress_type[c].suffix);
		if (noaction)
			printf("\trm -f %s\n", zfile1);
		else
			(void) unlink(zfile1);
	}
}