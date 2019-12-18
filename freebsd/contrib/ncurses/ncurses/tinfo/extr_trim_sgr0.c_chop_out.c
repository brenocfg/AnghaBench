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
 int /*<<< orphan*/  TR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE_DATABASE ; 
 int /*<<< orphan*/  _nc_visbuf (char*) ; 

__attribute__((used)) static unsigned
chop_out(char *string, unsigned i, unsigned j)
{
    TR(TRACE_DATABASE, ("chop_out %d..%d from %s", i, j, _nc_visbuf(string)));
    while (string[j] != '\0') {
	string[i++] = string[j++];
    }
    string[i] = '\0';
    return i;
}