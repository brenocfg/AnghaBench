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
struct protoent {char* p_name; int p_proto; } ;

/* Variables and functions */
 int atoi (char const*) ; 
 struct protoent* bt_getprotobyname (char const*) ; 
 struct protoent* bt_getprotobynumber (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
protomode(char const *arg, int brief)
{
	struct protoent	*pe = NULL;
	int		 proto;

	if ((proto = atoi(arg)) != 0)
		pe = bt_getprotobynumber(proto);
	else
		pe = bt_getprotobyname(arg);

	if (pe == NULL) {
		fprintf(stderr, "%s: Unknown Protocol/Service Multiplexor\n", arg);
		return (1);
	}

	if (brief) {
		if (proto)
			printf("%s", pe->p_name);
		else
			printf("%d", pe->p_proto);
	} else {
		printf("Protocol/Service Multiplexor %s has number %d\n",
			pe->p_name, pe->p_proto);
	}

	return (0);
}