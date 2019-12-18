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
struct mbuf {int m_len; int /*<<< orphan*/ * m_next; } ;
struct coalesce_info {int count; int nbytes; } ;

/* Variables and functions */

__attribute__((used)) static int
coalesce_check(struct mbuf *m, void *arg)
{
	struct coalesce_info *ci = arg;
	int *count = &ci->count;
	int *nbytes = &ci->nbytes;

	if ((*nbytes == 0) || ((*nbytes + m->m_len <= 10500) &&
		(*count < 7) && (m->m_next == NULL))) {
		*count += 1;
		*nbytes += m->m_len;
		return (1);
	}
	return (0);
}