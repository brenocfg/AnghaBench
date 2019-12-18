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
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 int find_unique_abbrev_r (char*,struct object_id const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int measure_abbrev(const struct object_id *oid, int sofar)
{
	char hex[GIT_MAX_HEXSZ + 1];
	int w = find_unique_abbrev_r(hex, oid, DEFAULT_ABBREV);

	return (w < sofar) ? sofar : w;
}