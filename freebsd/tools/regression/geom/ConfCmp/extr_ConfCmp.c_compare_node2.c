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
struct node {int dummy; } ;

/* Variables and functions */
 int compare_node (struct node*,struct node*,int) ; 
 int /*<<< orphan*/  indent (int) ; 
 int /*<<< orphan*/  print_node (struct node*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
compare_node2(struct node *n1, struct node *n2, int in)
{
	int i;

	i = compare_node(n1, n2, in);
	if (i) {
		printf("1>");
		indent(in);
		print_node(n1);
		printf("2>");
		indent(in);
		print_node(n2);
	}
	return (i);
}