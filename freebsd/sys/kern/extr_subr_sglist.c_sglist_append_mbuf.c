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
struct mbuf {scalar_t__ m_len; int m_flags; int /*<<< orphan*/  m_data; struct mbuf* m_next; } ;

/* Variables and functions */
 int EINVAL ; 
 int M_NOMAP ; 
 int /*<<< orphan*/  SGLIST_RESTORE (struct sglist*,struct sgsave) ; 
 int /*<<< orphan*/  SGLIST_SAVE (struct sglist*,struct sgsave) ; 
 int sglist_append (struct sglist*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sglist_append_mb_ext_pgs (struct sglist*,struct mbuf*) ; 

int
sglist_append_mbuf(struct sglist *sg, struct mbuf *m0)
{
	struct sgsave save;
	struct mbuf *m;
	int error;

	if (sg->sg_maxseg == 0)
		return (EINVAL);

	error = 0;
	SGLIST_SAVE(sg, save);
	for (m = m0; m != NULL; m = m->m_next) {
		if (m->m_len > 0) {
			if ((m->m_flags & M_NOMAP) != 0)
				error = sglist_append_mb_ext_pgs(sg, m);
			else
				error = sglist_append(sg, m->m_data,
				    m->m_len);
			if (error) {
				SGLIST_RESTORE(sg, save);
				return (error);
			}
		}
	}
	return (0);
}