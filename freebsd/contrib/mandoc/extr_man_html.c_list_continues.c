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
struct roff_node {scalar_t__ type; scalar_t__ tok; char* string; TYPE_1__* head; } ;
struct TYPE_2__ {struct roff_node* child; } ;

/* Variables and functions */
 scalar_t__ MAN_IP ; 
 scalar_t__ MAN_TP ; 
 scalar_t__ MAN_TQ ; 
 scalar_t__ ROFFT_BLOCK ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static char
list_continues(const struct roff_node *n1, const struct roff_node *n2)
{
	const char *s1, *s2;
	char c1, c2;

	if (n1 == NULL || n1->type != ROFFT_BLOCK ||
	    n2 == NULL || n2->type != ROFFT_BLOCK)
		return '\0';
	if ((n1->tok == MAN_TP || n1->tok == MAN_TQ) &&
	    (n2->tok == MAN_TP || n2->tok == MAN_TQ))
		return ' ';
	if (n1->tok != MAN_IP || n2->tok != MAN_IP)
		return '\0';
	n1 = n1->head->child;
	n2 = n2->head->child;
	s1 = n1 == NULL ? "" : n1->string;
	s2 = n2 == NULL ? "" : n2->string;
	c1 = strcmp(s1, "*") == 0 ? '*' :
	     strcmp(s1, "\\-") == 0 ? '-' :
	     strcmp(s1, "\\(bu") == 0 ? 'b' : ' ';
	c2 = strcmp(s2, "*") == 0 ? '*' :
	     strcmp(s2, "\\-") == 0 ? '-' :
	     strcmp(s2, "\\(bu") == 0 ? 'b' : ' ';
	return c1 != c2 ? '\0' : c1 == 'b' ? '*' : c1;
}