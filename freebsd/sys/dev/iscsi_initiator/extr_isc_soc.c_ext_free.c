#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ext_buf; TYPE_2__* ext_arg1; } ;
struct mbuf {TYPE_1__ m_ext; } ;
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_2__ pduq_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_ISCSIBUF ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ou_refcnt ; 

__attribute__((used)) static void
ext_free(struct mbuf *m)
{
     pduq_t *pq = m->m_ext.ext_arg1;

     if(pq->buf != NULL) {
	  debug(3, "ou_refcnt=%d a=%p b=%p",
	       ou_refcnt, m->m_ext.ext_buf, pq->buf);
	  free(pq->buf, M_ISCSIBUF);
	  pq->buf = NULL;
     }
}