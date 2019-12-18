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
struct indir {int total; int shift; void* array; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_MD ; 
 int /*<<< orphan*/  M_MDSECT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NINDIR ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int nshift ; 

__attribute__((used)) static struct indir *
dimension(off_t size)
{
	off_t rcnt;
	struct indir *ip;
	int layer;

	rcnt = size;
	layer = 0;
	while (rcnt > NINDIR) {
		rcnt /= NINDIR;
		layer++;
	}

	/*
	 * XXX: the top layer is probably not fully populated, so we allocate
	 * too much space for ip->array in here.
	 */
	ip = malloc(sizeof *ip, M_MD, M_WAITOK | M_ZERO);
	ip->array = malloc(sizeof(uintptr_t) * NINDIR,
	    M_MDSECT, M_WAITOK | M_ZERO);
	ip->total = NINDIR;
	ip->shift = layer * nshift;
	return (ip);
}