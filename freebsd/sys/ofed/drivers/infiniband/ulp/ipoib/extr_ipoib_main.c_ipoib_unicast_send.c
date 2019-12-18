#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct TYPE_3__ {scalar_t__ ifq_len; } ;
struct ipoib_path {TYPE_1__ queue; scalar_t__ query; scalar_t__ ah; int /*<<< orphan*/  valid; } ;
struct ipoib_header {scalar_t__ hwaddr; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 scalar_t__ IPOIB_MAX_PATH_REC_QUEUE ; 
 int /*<<< orphan*/  IPOIB_QPN (scalar_t__) ; 
 int /*<<< orphan*/  _IF_ENQUEUE (TYPE_1__*,struct mbuf*) ; 
 scalar_t__ _IF_QLEN (TYPE_1__*) ; 
 int /*<<< orphan*/  __path_add (struct ipoib_dev_priv*,struct ipoib_path*) ; 
 struct ipoib_path* __path_find (struct ipoib_dev_priv*,scalar_t__) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ipoib_cm_get (struct ipoib_path*) ; 
 int /*<<< orphan*/  ipoib_cm_send (struct ipoib_dev_priv*,struct mbuf*,scalar_t__) ; 
 scalar_t__ ipoib_cm_up (struct ipoib_path*) ; 
 int /*<<< orphan*/  ipoib_path_free (struct ipoib_dev_priv*,struct ipoib_path*) ; 
 int /*<<< orphan*/  ipoib_send (struct ipoib_dev_priv*,struct mbuf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct ipoib_path* path_rec_create (struct ipoib_dev_priv*,scalar_t__) ; 
 scalar_t__ path_rec_start (struct ipoib_dev_priv*,struct ipoib_path*) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipoib_unicast_send(struct mbuf *mb, struct ipoib_dev_priv *priv, struct ipoib_header *eh)
{
	struct ipoib_path *path;

	path = __path_find(priv, eh->hwaddr + 4);
	if (!path || !path->valid) {
		int new_path = 0;

		if (!path) {
			path = path_rec_create(priv, eh->hwaddr);
			new_path = 1;
		}
		if (path) {
			if (_IF_QLEN(&path->queue) < IPOIB_MAX_PATH_REC_QUEUE)
				_IF_ENQUEUE(&path->queue, mb);
			else {
				if_inc_counter(priv->dev, IFCOUNTER_OERRORS, 1);
				m_freem(mb);
			}

			if (!path->query && path_rec_start(priv, path)) {
				spin_unlock_irqrestore(&priv->lock, flags);
				if (new_path)
					ipoib_path_free(priv, path);
				return;
			} else
				__path_add(priv, path);
		} else {
			if_inc_counter(priv->dev, IFCOUNTER_OERRORS, 1);
			m_freem(mb);
		}

		return;
	}

	if (ipoib_cm_get(path) && ipoib_cm_up(path)) {
		ipoib_cm_send(priv, mb, ipoib_cm_get(path));
	} else if (path->ah) {
		ipoib_send(priv, mb, path->ah, IPOIB_QPN(eh->hwaddr));
	} else if ((path->query || !path_rec_start(priv, path)) &&
		    path->queue.ifq_len < IPOIB_MAX_PATH_REC_QUEUE) {
		_IF_ENQUEUE(&path->queue, mb);
	} else {
		if_inc_counter(priv->dev, IFCOUNTER_OERRORS, 1);
		m_freem(mb);
	}
}