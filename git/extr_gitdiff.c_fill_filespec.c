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
struct diff_filespec {int oid_valid; int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  canon_mode (unsigned short) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 

void fill_filespec(struct diff_filespec *spec, const struct object_id *oid,
		   int oid_valid, unsigned short mode)
{
	if (mode) {
		spec->mode = canon_mode(mode);
		oidcpy(&spec->oid, oid);
		spec->oid_valid = oid_valid;
	}
}