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
struct jobspec_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  process_jqe ;

/* Variables and functions */
 int /*<<< orphan*/  SCQ_JSORDER ; 
 int /*<<< orphan*/  STAILQ_INIT (struct jobspec_hdr*) ; 
 int /*<<< orphan*/  free_jobspec (struct jobspec_hdr*) ; 
 int /*<<< orphan*/  nitems ; 
 int parse_jobspec (char*,struct jobspec_hdr*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  queue ; 
 int scanq_jobspec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jobspec_hdr*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
process_jobs(int argc, char *argv[], process_jqe process_rtn, void *myinfo)
{
	struct jobspec_hdr jobs_wanted;
	int i, matchcnt, pjres;

	STAILQ_INIT(&jobs_wanted);
	for (i = 0; i < argc; i++) {
		pjres = parse_jobspec(argv[i], &jobs_wanted);
		if (pjres == 0) {
			printf("\tinvalid job specifier: %s\n", argv[i]);
			continue;
		}
	}
	matchcnt = scanq_jobspec(nitems, queue, SCQ_JSORDER, &jobs_wanted,
	    process_rtn, myinfo);

	free_jobspec(&jobs_wanted);
	return (matchcnt);
}