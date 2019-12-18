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
struct snmp_toolinfo {int dummy; } ;
struct fname {int /*<<< orphan*/  name; int /*<<< orphan*/  cut; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_close () ; 
 int /*<<< orphan*/  input_fopen (int /*<<< orphan*/ ) ; 
 int snmp_import (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  snmp_import_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

int32_t
snmp_import_file(struct snmp_toolinfo *snmptoolctx, struct fname *file)
{
	int idx;

	snmp_import_init(&(file->cut));
	input_fopen(file->name);
	if ((idx = snmp_import(snmptoolctx)) < 0)
		warnx("Failed to read mappings from file %s", file->name);

	input_close();

	return (idx);
}