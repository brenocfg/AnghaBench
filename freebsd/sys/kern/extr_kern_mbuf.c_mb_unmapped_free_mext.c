#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sf_buf {int dummy; } ;
struct TYPE_2__ {struct mbuf* ext_arg2; struct sf_buf* ext_arg1; } ;
struct mbuf {TYPE_1__ m_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb_free_ext (struct mbuf*) ; 
 int /*<<< orphan*/  sf_buf_free (struct sf_buf*) ; 

__attribute__((used)) static void
mb_unmapped_free_mext(struct mbuf *m)
{
	struct sf_buf *sf;
	struct mbuf *old_m;

	sf = m->m_ext.ext_arg1;
	sf_buf_free(sf);

	/* Drop the reference on the backing EXT_PGS mbuf. */
	old_m = m->m_ext.ext_arg2;
	mb_free_ext(old_m);
}