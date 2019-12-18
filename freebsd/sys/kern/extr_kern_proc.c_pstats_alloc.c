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
struct pstats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SUBPROC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct pstats* malloc (int,int /*<<< orphan*/ ,int) ; 

struct pstats *
pstats_alloc(void)
{

	return (malloc(sizeof(struct pstats), M_SUBPROC, M_ZERO|M_WAITOK));
}