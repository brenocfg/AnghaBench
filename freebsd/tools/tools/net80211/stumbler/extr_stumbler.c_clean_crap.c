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
struct node_info {struct node_info* next; } ;

/* Variables and functions */
 int bpf_s ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct node_info*) ; 
 int ioctl_s ; 
 struct node_info* nodes ; 

void clean_crap() {
	struct node_info* next;

	if (ioctl_s != -1)
		close(ioctl_s);
	if (bpf_s != -1)
		close(bpf_s);

	while (nodes) {
		next = nodes->next;
		free(nodes);
		nodes = next;
	}
}