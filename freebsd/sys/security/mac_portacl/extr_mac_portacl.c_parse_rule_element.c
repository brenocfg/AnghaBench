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
struct rule {void* r_port; int /*<<< orphan*/  r_protocol; int /*<<< orphan*/  r_idtype; void* r_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GID_STRING ; 
 int /*<<< orphan*/  M_PORTACL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RULE_GID ; 
 int /*<<< orphan*/  RULE_PROTO_TCP ; 
 int /*<<< orphan*/  RULE_PROTO_UDP ; 
 int /*<<< orphan*/  RULE_UID ; 
 int /*<<< orphan*/  TCP_STRING ; 
 int /*<<< orphan*/  UDP_STRING ; 
 int /*<<< orphan*/  UID_STRING ; 
 int /*<<< orphan*/  free (struct rule*,int /*<<< orphan*/ ) ; 
 struct rule* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 void* strtol (char*,char**,int) ; 

__attribute__((used)) static int
parse_rule_element(char *element, struct rule **rule)
{
	char *idtype, *id, *protocol, *portnumber, *p;
	struct rule *new;
	int error;

	error = 0;
	new = malloc(sizeof(*new), M_PORTACL, M_ZERO | M_WAITOK);

	idtype = strsep(&element, ":");
	if (idtype == NULL) {
		error = EINVAL;
		goto out;
	}
	id = strsep(&element, ":");
	if (id == NULL) {
		error = EINVAL;
		goto out;
	}
	new->r_id = strtol(id, &p, 10);
	if (*p != '\0') {
		error = EINVAL;
		goto out;
	}
	if (strcmp(idtype, UID_STRING) == 0)
		new->r_idtype = RULE_UID;
	else if (strcmp(idtype, GID_STRING) == 0)
		new->r_idtype = RULE_GID;
	else {
		error = EINVAL;
		goto out;
	}
	protocol = strsep(&element, ":");
	if (protocol == NULL) {
		error = EINVAL;
		goto out;
	}
	if (strcmp(protocol, TCP_STRING) == 0)
		new->r_protocol = RULE_PROTO_TCP;
	else if (strcmp(protocol, UDP_STRING) == 0)
		new->r_protocol = RULE_PROTO_UDP;
	else {
		error = EINVAL;
		goto out;
	}
	portnumber = element;
	if (portnumber == NULL) {
		error = EINVAL;
		goto out;
	}
	new->r_port = strtol(portnumber, &p, 10);
	if (*p != '\0') {
		error = EINVAL;
		goto out;
	}

out:
	if (error != 0) {
		free(new, M_PORTACL);
		*rule = NULL;
	} else
		*rule = new;
	return (error);
}