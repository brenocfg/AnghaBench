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
struct sglist_seg {int dummy; } ;
struct sglist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SGLIST ; 
 struct sglist* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sglist_init (struct sglist*,int,struct sglist_seg*) ; 

struct sglist *
sglist_alloc(int nsegs, int mflags)
{
	struct sglist *sg;

	sg = malloc(sizeof(struct sglist) + nsegs * sizeof(struct sglist_seg),
	    M_SGLIST, mflags);
	if (sg == NULL)
		return (NULL);
	sglist_init(sg, nsegs, (struct sglist_seg *)(sg + 1));
	return (sg);
}