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
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {char* counter_name; int cpu; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_CPU ; 
 int /*<<< orphan*/  build_counters_from_header (int /*<<< orphan*/ *) ; 
 TYPE_1__* cnts ; 
 int /*<<< orphan*/  command ; 
 int cpu_count_out ; 
 int /*<<< orphan*/  do_expression (int /*<<< orphan*/ ,int) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * glob_cpu ; 
 int /*<<< orphan*/  lace_cpus_together () ; 
 int max_to_collect ; 
 int /*<<< orphan*/  my_pclose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * my_popen (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int ncnts ; 
 int /*<<< orphan*/  print_header () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ read_a_line (int /*<<< orphan*/ *) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
process_file(char *filename)
{
	FILE *io;
	int i;
	int line_at, not_done;
	pid_t pid_of_command=0;

	if (filename ==  NULL) {
		io = my_popen(command, "r", &pid_of_command);
	} else {
		io = fopen(filename, "r");
		if (io == NULL) {
			printf("Can't process file %s err:%d\n",
			       filename, errno);
			return;
		}
	}
	build_counters_from_header(io);
	if (cnts == NULL) {
		/* Nothing we can do */
		printf("Nothing to do -- no counters built\n");
		if (io) {
			fclose(io);
		}
		return;
	}
	lace_cpus_together();
	print_header();
	if (verbose) {
		for (i=0; i<ncnts; i++) {
			printf("Counter:%s cpu:%d index:%d\n",
			       cnts[i].counter_name,
			       cnts[i].cpu, i);
		}
	}
	line_at = 0;
	not_done = 1;
	while(not_done) {
		if (read_a_line(io)) {
			line_at++;
		} else {
			break;
		}
		if (line_at >= max_to_collect) {
			not_done = 0;
		}
		if (filename == NULL) {
			int cnt;
			/* For the ones we dynamically open we print now */
			for(i=0, cnt=0; i<MAX_CPU; i++) {
				do_expression(glob_cpu[i], (line_at-1));
				cnt++;
				if (cnt == cpu_count_out) {
					printf("\n");
					break;
				} else {
					printf("\t");
				}
			}
		}
	}
	if (filename) {
		fclose(io);
	} else {
		my_pclose(io, pid_of_command);
	}
}