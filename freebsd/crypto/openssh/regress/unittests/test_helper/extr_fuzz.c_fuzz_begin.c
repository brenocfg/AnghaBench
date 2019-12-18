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
typedef  int u_int ;
struct fuzz {size_t slen; int strategies; int /*<<< orphan*/ * seed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_DBG (char*) ; 
 int FUZZ_MAX ; 
 int /*<<< orphan*/  SIGINFO ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 struct fuzz* calloc (int,int) ; 
 int /*<<< orphan*/  fuzz_next (struct fuzz*) ; 
 struct fuzz* last_fuzz ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  siginfo ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct fuzz *
fuzz_begin(u_int strategies, const void *p, size_t l)
{
	struct fuzz *ret = calloc(sizeof(*ret), 1);

	assert(p != NULL);
	assert(ret != NULL);
	ret->seed = malloc(l);
	assert(ret->seed != NULL);
	memcpy(ret->seed, p, l);
	ret->slen = l;
	ret->strategies = strategies;

	assert(ret->slen < SIZE_MAX / 8);
	assert(ret->strategies <= (FUZZ_MAX|(FUZZ_MAX-1)));

	FUZZ_DBG(("begin, ret = %p", ret));

	fuzz_next(ret);

#ifdef SIGINFO
	last_fuzz = ret;
	signal(SIGINFO, siginfo);
#endif

	return ret;
}