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
struct sgsave {int dummy; } ;
struct sglist {scalar_t__ sg_maxseg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SGLIST_RESTORE (struct sglist*,struct sgsave) ; 
 int /*<<< orphan*/  SGLIST_SAVE (struct sglist*,struct sgsave) ; 
 int _sglist_append_buf (struct sglist*,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
sglist_append(struct sglist *sg, void *buf, size_t len)
{
	struct sgsave save;
	int error;

	if (sg->sg_maxseg == 0)
		return (EINVAL);
	SGLIST_SAVE(sg, save);
	error = _sglist_append_buf(sg, buf, len, NULL, NULL);
	if (error)
		SGLIST_RESTORE(sg, save);
	return (error);
}