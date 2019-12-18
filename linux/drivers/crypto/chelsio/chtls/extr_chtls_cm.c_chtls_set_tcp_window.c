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
typedef  int u8 ;
struct TYPE_2__ {unsigned int speed; } ;
struct port_info {TYPE_1__ link_cfg; } ;
struct net_device {int dummy; } ;
struct chtls_sock {int rcv_win; int snd_win; struct net_device* egress_dev; } ;

/* Variables and functions */
 int CHTLS_10G_RCVWIN ; 
 int CHTLS_10G_SNDWIN ; 
 unsigned int SPEED_10000 ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void chtls_set_tcp_window(struct chtls_sock *csk)
{
	struct net_device *ndev = csk->egress_dev;
	struct port_info *pi = netdev_priv(ndev);
	unsigned int linkspeed;
	u8 scale;

	linkspeed = pi->link_cfg.speed;
	scale = linkspeed / SPEED_10000;
#define CHTLS_10G_RCVWIN (256 * 1024)
	csk->rcv_win = CHTLS_10G_RCVWIN;
	if (scale)
		csk->rcv_win *= scale;
#define CHTLS_10G_SNDWIN (256 * 1024)
	csk->snd_win = CHTLS_10G_SNDWIN;
	if (scale)
		csk->snd_win *= scale;
}