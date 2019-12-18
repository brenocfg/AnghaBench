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
struct counters {char const* counter_name; struct counters* next_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static struct counters *
find_counter(struct counters *base, const char *name)
{
	struct counters *at;
	int len;

	at = base;
	len = strlen(name);
	while(at) {
		if (strncmp(at->counter_name, name, len) == 0) {
			return(at);
		}
		at = at->next_cpu;
	}
	printf("Can't find counter %s\n", name);
	printf("We have:\n");
	at = base;
	while(at) {
		printf("- %s\n", at->counter_name);
		at = at->next_cpu;
	}
	exit(-1);
}