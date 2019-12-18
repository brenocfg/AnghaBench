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

/* Variables and functions */
 int /*<<< orphan*/  brief ; 
 int /*<<< orphan*/  dump_all ; 
 int /*<<< orphan*/  multicast ; 
 int /*<<< orphan*/  node_name_map_file ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static int process_opt(void *context, int ch, char *optarg)
{
	switch (ch) {
	case 'a':
		dump_all++;
		break;
	case 'M':
		multicast++;
		break;
	case 'n':
		brief++;
		break;
	case 1:
		node_name_map_file = strdup(optarg);
		break;
	default:
		return -1;
	}
	return 0;
}