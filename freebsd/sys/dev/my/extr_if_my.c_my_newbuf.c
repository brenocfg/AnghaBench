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
struct my_softc {int /*<<< orphan*/  my_dev; } ;
struct my_chain_onefrag {TYPE_1__* my_ptr; struct mbuf* my_mbuf; } ;
struct mbuf {int dummy; } ;
struct TYPE_2__ {int my_ctl; int /*<<< orphan*/  my_status; int /*<<< orphan*/  my_data; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGETHDR (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int /*<<< orphan*/  MY_OWNByNIC ; 
 int MY_RBSShift ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
my_newbuf(struct my_softc * sc, struct my_chain_onefrag * c)
{
	struct mbuf    *m_new = NULL;

	MY_LOCK_ASSERT(sc);
	MGETHDR(m_new, M_NOWAIT, MT_DATA);
	if (m_new == NULL) {
		device_printf(sc->my_dev,
		    "no memory for rx list -- packet dropped!\n");
		return (ENOBUFS);
	}
	if (!(MCLGET(m_new, M_NOWAIT))) {
		device_printf(sc->my_dev,
		    "no memory for rx list -- packet dropped!\n");
		m_freem(m_new);
		return (ENOBUFS);
	}
	c->my_mbuf = m_new;
	c->my_ptr->my_data = vtophys(mtod(m_new, caddr_t));
	c->my_ptr->my_ctl = (MCLBYTES - 1) << MY_RBSShift;
	c->my_ptr->my_status = MY_OWNByNIC;
	return (0);
}