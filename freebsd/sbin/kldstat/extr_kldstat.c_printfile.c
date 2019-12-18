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
struct kld_file_stat {int version; int id; int refs; char* address; char* pathname; int /*<<< orphan*/  name; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_DECIMAL ; 
 int HN_NOSPACE ; 
 int /*<<< orphan*/  POINTER_WIDTH ; 
 int /*<<< orphan*/  err (int,char*,int) ; 
 int /*<<< orphan*/  humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int kldfirstmod (int) ; 
 scalar_t__ kldstat (int,struct kld_file_stat*) ; 
 int modfnext (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printmod (int) ; 

__attribute__((used)) static void
printfile(int fileid, int verbose, int humanized)
{
    struct kld_file_stat stat;
    int modid;
    char buf[5];

    stat.version = sizeof(struct kld_file_stat);
    if (kldstat(fileid, &stat) < 0) {
	err(1, "can't stat file id %d", fileid);
    } else {
	if (humanized) {
		humanize_number(buf, sizeof(buf), stat.size,
		    "", HN_AUTOSCALE, HN_DECIMAL | HN_NOSPACE);

		printf("%2d %4d %*p %5s %s",
		    stat.id, stat.refs, POINTER_WIDTH, stat.address, buf,
		    stat.name);
	} else {
		printf("%2d %4d %*p %8zx %s",
		    stat.id, stat.refs, POINTER_WIDTH, stat.address, stat.size,
		    stat.name);
	}
    }

    if (verbose) {
	printf(" (%s)\n", stat.pathname);
	printf("\tContains modules:\n");
	printf("\t\t Id Name\n");
	for (modid = kldfirstmod(fileid); modid > 0;
	     modid = modfnext(modid))
	    printmod(modid);
    } else
	printf("\n");
}