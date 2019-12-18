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
struct bitset {int /*<<< orphan*/ * __bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ZERO (int,struct bitset*) ; 
 int __bitset_words (int) ; 
 scalar_t__ isxdigit (char const) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bitset_strscan(struct bitset *set, int setlen, const char *buf)
{
	int i, ret;
	const char *p;

	BIT_ZERO(setlen, set);
	p = buf;
	for (i = 0; i < __bitset_words(setlen); i++) {
		if (*p == ',') {
			p++;
			continue;
		}
		ret = sscanf(p, "%lx", &set->__bits[i]);
		if (ret == 0 || ret == -1)
			break;
		while (isxdigit(*p))
			p++;
	}
	return (p - buf);
}