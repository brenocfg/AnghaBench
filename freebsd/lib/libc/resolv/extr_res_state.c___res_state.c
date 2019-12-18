#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* res_state ;
struct TYPE_10__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TIMEOUT ; 
 TYPE_1__ _res ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* res_check_reload (TYPE_1__*) ; 
 int /*<<< orphan*/  res_init_once ; 
 int /*<<< orphan*/  res_key ; 
 int /*<<< orphan*/  res_keycreate ; 
 int /*<<< orphan*/  res_thr_keycreated ; 
 TYPE_1__* thr_getspecific (int /*<<< orphan*/ ) ; 
 scalar_t__ thr_main () ; 
 scalar_t__ thr_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ thr_setspecific (int /*<<< orphan*/ ,TYPE_1__*) ; 

res_state
__res_state(void)
{
	res_state statp;

	if (thr_main() != 0)
		return res_check_reload(&_res);

	if (thr_once(&res_init_once, res_keycreate) != 0 ||
	    !res_thr_keycreated)
		return (&_res);

	statp = thr_getspecific(res_key);
	if (statp != NULL)
		return res_check_reload(statp);
	statp = calloc(1, sizeof(*statp));
	if (statp == NULL)
		return (&_res);
#ifdef __BIND_RES_TEXT
	statp->options = RES_TIMEOUT;			/* Motorola, et al. */
#endif
	if (thr_setspecific(res_key, statp) == 0)
		return (statp);
	free(statp);
	return (&_res);
}