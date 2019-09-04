#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int anchors_nr; int /*<<< orphan*/ * anchors; } ;
typedef  TYPE_1__ xpparam_t ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_anchor(xpparam_t const *xpp, const char *line)
{
	int i;
	for (i = 0; i < xpp->anchors_nr; i++) {
		if (!strncmp(line, xpp->anchors[i], strlen(xpp->anchors[i])))
			return 1;
	}
	return 0;
}