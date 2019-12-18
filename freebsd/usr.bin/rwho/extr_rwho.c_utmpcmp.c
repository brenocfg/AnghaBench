#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  out_line; int /*<<< orphan*/  out_name; } ;
struct TYPE_4__ {TYPE_1__ myutmp; int /*<<< orphan*/  myhost; } ;

/* Variables and functions */
 TYPE_2__* MYUTMP (void const*) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
utmpcmp(const void *u1, const void *u2)
{
	int rc;

	rc = strncmp(MYUTMP(u1)->myutmp.out_name, MYUTMP(u2)->myutmp.out_name,
	    sizeof(MYUTMP(u2)->myutmp.out_name));
	if (rc != 0)
		return (rc);
	rc = strcmp(MYUTMP(u1)->myhost, MYUTMP(u2)->myhost);
	if (rc != 0)
		return (rc);
	return (strncmp(MYUTMP(u1)->myutmp.out_line,
	    MYUTMP(u2)->myutmp.out_line, sizeof(MYUTMP(u2)->myutmp.out_line)));
}