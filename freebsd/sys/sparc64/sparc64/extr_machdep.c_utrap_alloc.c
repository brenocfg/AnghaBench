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
struct md_utrap {int ut_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SUBPROC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct md_utrap* malloc (int,int /*<<< orphan*/ ,int) ; 

struct md_utrap *
utrap_alloc(void)
{
	struct md_utrap *ut;

	ut = malloc(sizeof(struct md_utrap), M_SUBPROC, M_WAITOK | M_ZERO);
	ut->ut_refcnt = 1;
	return (ut);
}