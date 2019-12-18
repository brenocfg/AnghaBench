#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {int /*<<< orphan*/  rs_chacha; } ;

/* Variables and functions */
 size_t IVSZ ; 
 size_t KEYSZ ; 
 int MAP_ANON ; 
 TYPE_1__* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_INHERIT_ZERO ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chacha_ivsetup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chacha_keysetup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 int minherit (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* rs ; 
 TYPE_1__* rsx ; 

__attribute__((used)) static inline void
_rs_init(u_char *buf, size_t n)
{
	assert(buf);
	if (n < KEYSZ + IVSZ)
		return;

	if (rs == NULL) {
#ifndef UB_ON_WINDOWS
		if ((rs = mmap(NULL, sizeof(*rs), PROT_READ|PROT_WRITE,
		    MAP_ANON|MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			abort();
#ifdef MAP_INHERIT_ZERO
		if (minherit(rs, sizeof(*rs), MAP_INHERIT_ZERO) == -1)
			abort();
#endif
#else /* WINDOWS */
		rs = malloc(sizeof(*rs));
		if(!rs)
			abort();
#endif
	}
	if (rsx == NULL) {
#ifndef UB_ON_WINDOWS
		if ((rsx = mmap(NULL, sizeof(*rsx), PROT_READ|PROT_WRITE,
		    MAP_ANON|MAP_PRIVATE, -1, 0)) == MAP_FAILED)
			abort();
#else /* WINDOWS */
		rsx = malloc(sizeof(*rsx));
		if(!rsx)
			abort();
#endif
	}

	chacha_keysetup(&rsx->rs_chacha, buf, KEYSZ * 8, 0);
	chacha_ivsetup(&rsx->rs_chacha, buf + KEYSZ);
}