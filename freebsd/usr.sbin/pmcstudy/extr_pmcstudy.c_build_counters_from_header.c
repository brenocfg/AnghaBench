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
struct counters {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * cnts ; 
 int errno ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int ncnts ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  process_header (int,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
build_counters_from_header(FILE *io)
{
	char buffer[8192], *p;
	int i, len, cnt;
	size_t mlen;

	/* We have a new start, lets 
	 * setup our headers and cpus.
	 */
	if (fgets(buffer, sizeof(buffer), io) == NULL) {
		printf("First line can't be read from file err:%d\n", errno);
		return;
	}
	/*
	 * Ok output is an array of counters. Once
	 * we start to read the values in we must
	 * put them in there slot to match there CPU and 
	 * counter being updated. We create a mass array
	 * of the counters, filling in the CPU and 
	 * counter name. 
	 */
	/* How many do we get? */
	len = strlen(buffer);
	for (i=0, cnt=0; i<len; i++) {
		if (strncmp(&buffer[i], "s/", 2) == 0) {
			cnt++;
			for(;i<len;i++) {
				if (buffer[i] == ' ')
					break;
			}
		}
	}
	mlen = sizeof(struct counters) * cnt;
	cnts = malloc(mlen);
	ncnts = cnt;
	if (cnts == NULL) {
		printf("No memory err:%d\n", errno);
		return;
	}
	memset(cnts, 0, mlen);
	for (i=0, cnt=0; i<len; i++) {
		if (strncmp(&buffer[i], "s/", 2) == 0) {
			p = &buffer[i];
			for(;i<len;i++) {
				if (buffer[i] == ' ') {
					buffer[i] = 0;
					break;
				}
			}
			process_header(cnt, p);
			cnt++;
		}
	}
	if (verbose)
		printf("We have %d entries\n", cnt);	
}