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
struct nv {scalar_t__ nv_magic; struct ebuf* nv_ebuf; scalar_t__ nv_error; } ;
struct ebuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ NV_MAGIC ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebuf_del_tail (struct ebuf*,size_t) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct nv*) ; 
 struct nv* malloc (int) ; 
 int nv_validate (struct nv*,size_t*) ; 

struct nv *
nv_ntoh(struct ebuf *eb)
{
	struct nv *nv;
	size_t extra;
	int rerrno;

	PJDLOG_ASSERT(eb != NULL);

	nv = malloc(sizeof(*nv));
	if (nv == NULL)
		return (NULL);
	nv->nv_error = 0;
	nv->nv_ebuf = eb;
	nv->nv_magic = NV_MAGIC;

	if (nv_validate(nv, &extra) == -1) {
		rerrno = errno;
		nv->nv_magic = 0;
		free(nv);
		errno = rerrno;
		return (NULL);
	}
	/*
	 * Remove extra zeros at the end of the buffer.
	 */
	ebuf_del_tail(eb, extra);

	return (nv);
}