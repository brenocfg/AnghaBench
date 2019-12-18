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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
#define  AT_CANARY 136 
#define  AT_EXECPATH 135 
#define  AT_HWCAP 134 
#define  AT_HWCAP2 133 
#define  AT_NCPUS 132 
#define  AT_OSRELDATE 131 
#define  AT_PAGESIZES 130 
#define  AT_PAGESZ 129 
#define  AT_TIMEKEEP 128 
 int EINVAL ; 
 int ENOENT ; 
 int ENOSYS ; 
 int /*<<< orphan*/ * __elf_aux_vector ; 
 int /*<<< orphan*/  __init_elf_aux_vector () ; 
 int /*<<< orphan*/  _once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aux_once ; 
 int /*<<< orphan*/ * canary ; 
 int canary_len ; 
 int /*<<< orphan*/ * execpath ; 
 int /*<<< orphan*/  hwcap ; 
 int /*<<< orphan*/  hwcap2 ; 
 int /*<<< orphan*/  hwcap2_present ; 
 int /*<<< orphan*/  hwcap_present ; 
 int /*<<< orphan*/  init_aux ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ncpus ; 
 int osreldate ; 
 int pagesize ; 
 int /*<<< orphan*/ * pagesizes ; 
 int pagesizes_len ; 
 int strlcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * timekeep ; 

int
_elf_aux_info(int aux, void *buf, int buflen)
{
	int res;

	__init_elf_aux_vector();
	if (__elf_aux_vector == NULL)
		return (ENOSYS);
	_once(&aux_once, init_aux);

	switch (aux) {
	case AT_CANARY:
		if (canary != NULL && canary_len >= buflen) {
			memcpy(buf, canary, buflen);
			memset(canary, 0, canary_len);
			canary = NULL;
			res = 0;
		} else
			res = ENOENT;
		break;
	case AT_EXECPATH:
		if (execpath == NULL)
			res = ENOENT;
		else if (buf == NULL)
			res = EINVAL;
		else {
			if (strlcpy(buf, execpath, buflen) >= buflen)
				res = EINVAL;
			else
				res = 0;
		}
		break;
	case AT_HWCAP:
		if (hwcap_present && buflen == sizeof(u_long)) {
			*(u_long *)buf = hwcap;
			res = 0;
		} else
			res = ENOENT;
		break;
	case AT_HWCAP2:
		if (hwcap2_present && buflen == sizeof(u_long)) {
			*(u_long *)buf = hwcap2;
			res = 0;
		} else
			res = ENOENT;
		break;
	case AT_PAGESIZES:
		if (pagesizes != NULL && pagesizes_len >= buflen) {
			memcpy(buf, pagesizes, buflen);
			res = 0;
		} else
			res = ENOENT;
		break;
	case AT_PAGESZ:
		if (buflen == sizeof(int)) {
			if (pagesize != 0) {
				*(int *)buf = pagesize;
				res = 0;
			} else
				res = ENOENT;
		} else
			res = EINVAL;
		break;
	case AT_OSRELDATE:
		if (buflen == sizeof(int)) {
			if (osreldate != 0) {
				*(int *)buf = osreldate;
				res = 0;
			} else
				res = ENOENT;
		} else
			res = EINVAL;
		break;
	case AT_NCPUS:
		if (buflen == sizeof(int)) {
			if (ncpus != 0) {
				*(int *)buf = ncpus;
				res = 0;
			} else
				res = ENOENT;
		} else
			res = EINVAL;
		break;
	case AT_TIMEKEEP:
		if (buflen == sizeof(void *)) {
			if (timekeep != NULL) {
				*(void **)buf = timekeep;
				res = 0;
			} else
				res = ENOENT;
		} else
			res = EINVAL;
		break;
	default:
		res = ENOENT;
		break;
	}
	return (res);
}