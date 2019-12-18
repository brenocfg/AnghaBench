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
typedef  scalar_t__ u_int8_t ;
typedef  int u_int16_t ;
struct servent {char* s_name; } ;
typedef  int /*<<< orphan*/  a2 ;
typedef  int /*<<< orphan*/  a1 ;

/* Variables and functions */
 scalar_t__ PF_OP_EQ ; 
 scalar_t__ PF_OP_NE ; 
 struct servent* getservbyport (int,char const*) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  print_op (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void
print_port(u_int8_t op, u_int16_t p1, u_int16_t p2, const char *proto, int numeric)
{
	char		 a1[6], a2[6];
	struct servent	*s;

	if (!numeric)
		s = getservbyport(p1, proto);
	else
		s = NULL;
	p1 = ntohs(p1);
	p2 = ntohs(p2);
	snprintf(a1, sizeof(a1), "%u", p1);
	snprintf(a2, sizeof(a2), "%u", p2);
	printf(" port");
	if (s != NULL && (op == PF_OP_EQ || op == PF_OP_NE))
		print_op(op, s->s_name, a2);
	else
		print_op(op, a1, a2);
}