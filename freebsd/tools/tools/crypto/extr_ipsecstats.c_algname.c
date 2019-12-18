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
struct alg {int a; char const* name; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char*
algname(int a, const struct alg algs[], int nalgs)
{
	static char buf[80];
	int i;

	for (i = 0; i < nalgs; i++)
		if (algs[i].a == a)
			return algs[i].name;
	snprintf(buf, sizeof(buf), "alg#%u", a);
	return buf;
}