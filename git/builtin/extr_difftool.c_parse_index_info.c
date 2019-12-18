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
struct object_id {int dummy; } ;

/* Variables and functions */
 int error (char*,...) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 scalar_t__ parse_oid_hex (char*,struct object_id*,char const**) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int parse_index_info(char *p, int *mode1, int *mode2,
			    struct object_id *oid1, struct object_id *oid2,
			    char *status)
{
	if (*p != ':')
		return error("expected ':', got '%c'", *p);
	*mode1 = (int)strtol(p + 1, &p, 8);
	if (*p != ' ')
		return error("expected ' ', got '%c'", *p);
	*mode2 = (int)strtol(p + 1, &p, 8);
	if (*p != ' ')
		return error("expected ' ', got '%c'", *p);
	if (parse_oid_hex(++p, oid1, (const char **)&p))
		return error("expected object ID, got '%s'", p);
	if (*p != ' ')
		return error("expected ' ', got '%c'", *p);
	if (parse_oid_hex(++p, oid2, (const char **)&p))
		return error("expected object ID, got '%s'", p);
	if (*p != ' ')
		return error("expected ' ', got '%c'", *p);
	*status = *++p;
	if (!*status)
		return error("missing status");
	if (p[1] && !isdigit(p[1]))
		return error("unexpected trailer: '%s'", p + 1);
	return 0;
}