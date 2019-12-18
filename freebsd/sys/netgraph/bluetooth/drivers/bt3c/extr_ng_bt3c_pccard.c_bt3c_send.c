#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mbuf {scalar_t__ m_len; int /*<<< orphan*/ * m_data; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;
typedef  TYPE_1__* bt3c_softc_p ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  stat; int /*<<< orphan*/  dev; int /*<<< orphan*/  outq; } ;

/* Variables and functions */
 int BT3C_FIFO_SIZE ; 
 int BT3C_XMIT ; 
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IF_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  NG_BT3C_INFO (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  NG_BT3C_STAT_BYTES_SENT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NG_BT3C_STAT_PCKTS_SENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt3c_set_address (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bt3c_write (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  bt3c_write_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct mbuf* m_free (struct mbuf*) ; 
 int min (int,scalar_t__) ; 

__attribute__((used)) static void
bt3c_send(node_p node, hook_p hook, void *arg, int completed)
{
	bt3c_softc_p	 sc = (bt3c_softc_p) NG_NODE_PRIVATE(node);
	struct mbuf	*m = NULL;
	int		 i, wrote, len;

	if (sc == NULL)
		return;

	if (completed)
		sc->flags &= ~BT3C_XMIT;

	if (sc->flags & BT3C_XMIT)
		return;

	bt3c_set_address(sc, 0x7080);

	for (wrote = 0; wrote < BT3C_FIFO_SIZE; ) {
		IF_DEQUEUE(&sc->outq, m);
		if (m == NULL)
			break;

		while (m != NULL) {
			len = min((BT3C_FIFO_SIZE - wrote), m->m_len);

			for (i = 0; i < len; i++)
				bt3c_write_data(sc, m->m_data[i]);

			wrote += len;
			m->m_data += len;
			m->m_len -= len;

			if (m->m_len > 0)
				break;

			m = m_free(m);
		}

		if (m != NULL) {
			IF_PREPEND(&sc->outq, m);
			break;
		}

		NG_BT3C_STAT_PCKTS_SENT(sc->stat);
	}

	if (wrote > 0) {
		NG_BT3C_INFO(sc->dev, "Wrote %d bytes\n", wrote);
		NG_BT3C_STAT_BYTES_SENT(sc->stat, wrote);

		bt3c_write(sc, 0x7005, wrote);
		sc->flags |= BT3C_XMIT;
	}
}