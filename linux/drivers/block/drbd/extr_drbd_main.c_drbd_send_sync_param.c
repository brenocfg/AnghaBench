#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct p_rs_param_95 {int /*<<< orphan*/  csums_alg; int /*<<< orphan*/  verify_alg; void* c_max_rate; void* c_fill_target; void* c_delay_target; void* c_plan_ahead; void* resync_rate; } ;
struct p_rs_param_89 {int dummy; } ;
struct p_rs_param {int dummy; } ;
struct net_conf {int /*<<< orphan*/  csums_alg; int /*<<< orphan*/  verify_alg; } ;
struct drbd_socket {int dummy; } ;
struct drbd_peer_device {TYPE_3__* device; TYPE_1__* connection; } ;
struct disk_conf {int /*<<< orphan*/  c_max_rate; int /*<<< orphan*/  c_fill_target; int /*<<< orphan*/  c_delay_target; int /*<<< orphan*/  c_plan_ahead; int /*<<< orphan*/  resync_rate; } ;
typedef  enum drbd_packet { ____Placeholder_drbd_packet } drbd_packet ;
struct TYPE_7__ {TYPE_2__* ldev; } ;
struct TYPE_6__ {int /*<<< orphan*/  disk_conf; } ;
struct TYPE_5__ {int agreed_pro_version; int /*<<< orphan*/  net_conf; struct drbd_socket data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRBD_C_DELAY_TARGET_DEF ; 
 int /*<<< orphan*/  DRBD_C_FILL_TARGET_DEF ; 
 int /*<<< orphan*/  DRBD_C_MAX_RATE_DEF ; 
 int /*<<< orphan*/  DRBD_C_PLAN_AHEAD_DEF ; 
 int /*<<< orphan*/  DRBD_RESYNC_RATE_DEF ; 
 int EIO ; 
 int P_SYNC_PARAM ; 
 int P_SYNC_PARAM89 ; 
 int SHARED_SECRET_MAX ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct p_rs_param_95* drbd_prepare_command (struct drbd_peer_device*,struct drbd_socket*) ; 
 int drbd_send_command (struct drbd_peer_device*,struct drbd_socket*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_ldev (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_ldev (TYPE_3__*) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int drbd_send_sync_param(struct drbd_peer_device *peer_device)
{
	struct drbd_socket *sock;
	struct p_rs_param_95 *p;
	int size;
	const int apv = peer_device->connection->agreed_pro_version;
	enum drbd_packet cmd;
	struct net_conf *nc;
	struct disk_conf *dc;

	sock = &peer_device->connection->data;
	p = drbd_prepare_command(peer_device, sock);
	if (!p)
		return -EIO;

	rcu_read_lock();
	nc = rcu_dereference(peer_device->connection->net_conf);

	size = apv <= 87 ? sizeof(struct p_rs_param)
		: apv == 88 ? sizeof(struct p_rs_param)
			+ strlen(nc->verify_alg) + 1
		: apv <= 94 ? sizeof(struct p_rs_param_89)
		: /* apv >= 95 */ sizeof(struct p_rs_param_95);

	cmd = apv >= 89 ? P_SYNC_PARAM89 : P_SYNC_PARAM;

	/* initialize verify_alg and csums_alg */
	memset(p->verify_alg, 0, 2 * SHARED_SECRET_MAX);

	if (get_ldev(peer_device->device)) {
		dc = rcu_dereference(peer_device->device->ldev->disk_conf);
		p->resync_rate = cpu_to_be32(dc->resync_rate);
		p->c_plan_ahead = cpu_to_be32(dc->c_plan_ahead);
		p->c_delay_target = cpu_to_be32(dc->c_delay_target);
		p->c_fill_target = cpu_to_be32(dc->c_fill_target);
		p->c_max_rate = cpu_to_be32(dc->c_max_rate);
		put_ldev(peer_device->device);
	} else {
		p->resync_rate = cpu_to_be32(DRBD_RESYNC_RATE_DEF);
		p->c_plan_ahead = cpu_to_be32(DRBD_C_PLAN_AHEAD_DEF);
		p->c_delay_target = cpu_to_be32(DRBD_C_DELAY_TARGET_DEF);
		p->c_fill_target = cpu_to_be32(DRBD_C_FILL_TARGET_DEF);
		p->c_max_rate = cpu_to_be32(DRBD_C_MAX_RATE_DEF);
	}

	if (apv >= 88)
		strcpy(p->verify_alg, nc->verify_alg);
	if (apv >= 89)
		strcpy(p->csums_alg, nc->csums_alg);
	rcu_read_unlock();

	return drbd_send_command(peer_device, sock, cmd, size, NULL, 0);
}