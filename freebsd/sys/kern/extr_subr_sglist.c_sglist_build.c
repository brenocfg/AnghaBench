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
struct sglist {int dummy; } ;

/* Variables and functions */
 struct sglist* sglist_alloc (int,int) ; 
 scalar_t__ sglist_append (struct sglist*,void*,size_t) ; 
 int sglist_count (void*,size_t) ; 
 int /*<<< orphan*/  sglist_free (struct sglist*) ; 

struct sglist *
sglist_build(void *buf, size_t len, int mflags)
{
	struct sglist *sg;
	int nsegs;

	if (len == 0)
		return (NULL);

	nsegs = sglist_count(buf, len);
	sg = sglist_alloc(nsegs, mflags);
	if (sg == NULL)
		return (NULL);
	if (sglist_append(sg, buf, len) != 0) {
		sglist_free(sg);
		return (NULL);
	}
	return (sg);
}