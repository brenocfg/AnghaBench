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
 int /*<<< orphan*/  FILEOBJ ; 
 int /*<<< orphan*/  MSGQIDOBJ ; 
 int /*<<< orphan*/  OPT_of ; 
 int /*<<< orphan*/  OPT_om ; 
 int /*<<< orphan*/  OPT_op ; 
 int /*<<< orphan*/  OPT_ose ; 
 int /*<<< orphan*/  OPT_osh ; 
 int /*<<< orphan*/  OPT_oso ; 
 int /*<<< orphan*/  PIDOBJ ; 
 int /*<<< orphan*/  SEMIDOBJ ; 
 int /*<<< orphan*/  SETOPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMIDOBJ ; 
 int /*<<< orphan*/  SOCKOBJ ; 
 int /*<<< orphan*/  opttochk ; 
 char* p_fileobj ; 
 char* p_msgqobj ; 
 char* p_pidobj ; 
 char* p_semobj ; 
 char* p_shmobj ; 
 char* p_sockobj ; 
 int /*<<< orphan*/  parse_regexp (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

__attribute__((used)) static void
parse_object_type(char *name, char *val)
{
	if (val == NULL)
		return;

	if (!strcmp(name, FILEOBJ)) {
		p_fileobj = val;
		parse_regexp(val);
		SETOPT(opttochk, OPT_of);
	} else if (!strcmp(name, MSGQIDOBJ)) {
		p_msgqobj = val;
		SETOPT(opttochk, OPT_om);
	} else if (!strcmp(name, PIDOBJ)) {
		p_pidobj = val;
		SETOPT(opttochk, OPT_op);
	} else if (!strcmp(name, SEMIDOBJ)) {
		p_semobj = val;
		SETOPT(opttochk, OPT_ose);
	} else if (!strcmp(name, SHMIDOBJ)) {
		p_shmobj = val;
		SETOPT(opttochk, OPT_osh);
	} else if (!strcmp(name, SOCKOBJ)) {
		p_sockobj = val;
		SETOPT(opttochk, OPT_oso);
	} else
		usage("unknown value for -o");
}