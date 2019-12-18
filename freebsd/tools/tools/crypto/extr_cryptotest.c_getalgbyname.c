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
struct alg {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct alg* algorithms ; 
 int nitems (struct alg*) ; 
 scalar_t__ streq (char const*,int /*<<< orphan*/ ) ; 

struct alg*
getalgbyname(const char* name)
{
	int i;

	for (i = 0; i < nitems(algorithms); i++)
		if (streq(name, algorithms[i].name))
			return &algorithms[i];
	return NULL;
}