#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct isoent {int ext_off; scalar_t__ identifier; TYPE_1__* parent; } ;
struct TYPE_2__ {int dir_number; } ;

/* Variables and functions */
 int memcmp (unsigned char const*,unsigned char const*,int) ; 

__attribute__((used)) static int
_compare_path_table_joliet(const void *v1, const void *v2)
{
	const struct isoent *p1, *p2;
	const unsigned char *s1, *s2;
	int cmp, l;

	p1 = *((const struct isoent **)(uintptr_t)v1);
	p2 = *((const struct isoent **)(uintptr_t)v2);

	/* Compare parent directory number */
	cmp = p1->parent->dir_number - p2->parent->dir_number;
	if (cmp != 0)
		return (cmp);

	/* Compare identifier */
	s1 = (const unsigned char *)p1->identifier;
	s2 = (const unsigned char *)p2->identifier;
	l = p1->ext_off;
	if (l > p2->ext_off)
		l = p2->ext_off;
	cmp = memcmp(s1, s2, l);
	if (cmp != 0)
		return (cmp);
	if (p1->ext_off < p2->ext_off) {
		s2 += l;
		l = p2->ext_off - p1->ext_off;
		while (l--)
			if (0 != *s2++)
				return (- *(const unsigned char *)(s2 - 1));
	} else if (p1->ext_off > p2->ext_off) {
		s1 += l;
		l = p1->ext_off - p2->ext_off;
		while (l--)
			if (0 != *s1++)
				return (*(const unsigned char *)(s1 - 1));
	}
	return (0);
}