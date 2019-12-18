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
typedef  size_t u_int ;
struct alg {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct alg* algs ; 
 size_t nitems (struct alg*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct alg *
find_alg(const char *name)
{
	u_int i;

	for (i = 0; i < nitems(algs); i++)
		if (strcasecmp(algs[i].name, name) == 0)
			return (&algs[i]);
	return (NULL);
}