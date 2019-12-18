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
struct group {int dummy; } ;

/* Variables and functions */
 struct group _gr_group ; 
 int /*<<< orphan*/  _gr_stayopen ; 
 int /*<<< orphan*/  endgrent () ; 
 int grscan (int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  grstart () ; 

__attribute__((used)) static struct group *
gi_getgrnam(const char *name)
{
	int rval;

	if (!grstart())
		return NULL;
	rval = grscan(1, 0, name);
	if (!_gr_stayopen)
		endgrent();
	return (rval) ? &_gr_group : NULL;
}