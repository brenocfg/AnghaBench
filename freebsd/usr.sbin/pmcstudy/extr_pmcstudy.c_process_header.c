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
struct counters {int /*<<< orphan*/  counter_name; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int MAX_NLEN ; 
 struct counters* cnts ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
process_header(int idx, char *p)
{
	struct counters *up;
	int i, len, nlen;
	/* 
	 * Given header element idx, at p in
	 * form 's/NN/nameof'
	 * process the entry to pull out the name and
	 * the CPU number.
	 */
	if (strncmp(p, "s/", 2)) {
		printf("Check -- invalid header no s/ in %s\n",
		       p);
		return;
	}
	up = &cnts[idx];
	up->cpu = strtol(&p[2], NULL, 10);
	len = strlen(p);
	for (i=2; i<len; i++) {
		if (p[i] == '/') {
			nlen = strlen(&p[(i+1)]);
			if (nlen < (MAX_NLEN-1)) {
				strcpy(up->counter_name, &p[(i+1)]);
			} else {
				strncpy(up->counter_name, &p[(i+1)], (MAX_NLEN-1));
			}
		}
	}
}