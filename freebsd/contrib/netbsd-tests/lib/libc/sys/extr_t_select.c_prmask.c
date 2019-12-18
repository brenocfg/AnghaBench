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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * __bits; } ;
typedef  TYPE_1__ sigset_t ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  N (int /*<<< orphan*/ ,size_t) ; 
 size_t __arraycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 char xtoa (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
prmask(const sigset_t *m, char *buf, size_t len)
{
	size_t j = 2;
	assert(len >= 3 + sizeof(*m));
	buf[0] = '0';
	buf[1] = 'x';
#define N(p, a)	(((p) >> ((a) * 4)) & 0xf)
	for (size_t i = __arraycount(m->__bits); i > 0; i--) {
		uint32_t p = m->__bits[i - 1];
		for (size_t k = sizeof(p); k > 0; k--)
			buf[j++] = xtoa(N(p, k - 1));
	}
	buf[j] = '\0';
	return buf;
}