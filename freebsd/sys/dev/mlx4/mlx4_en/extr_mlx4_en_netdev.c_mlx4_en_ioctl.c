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
typedef  int u_long ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_en_priv {scalar_t__ gone; int /*<<< orphan*/  port; int /*<<< orphan*/  media; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; } ;
struct ifrsskey {int /*<<< orphan*/  ifrk_keylen; int /*<<< orphan*/  ifrk_key; void* ifrk_func; } ;
struct ifrsshash {int /*<<< orphan*/  ifrh_types; void* ifrh_func; } ;
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int if_hwassist; struct mlx4_en_priv* if_softc; } ;
struct ifi2creq {int len; int /*<<< orphan*/  data; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  i2c ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int CSUM_IP ; 
 int CSUM_IP6_TSO ; 
 int CSUM_IP_TSO ; 
 int CSUM_TCP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_UDP ; 
 int CSUM_UDP_IPV6 ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENXIO ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWFILTER ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_WOL_MAGIC ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int MLX4_RSS_IPV4 ; 
 int MLX4_RSS_IPV6 ; 
 int MLX4_RSS_TCP_IPV4 ; 
 int MLX4_RSS_TCP_IPV6 ; 
 int MLX4_RSS_UDP_IPV4 ; 
 int MLX4_RSS_UDP_IPV6 ; 
 void* RSS_FUNC_TOEPLITZ ; 
 int /*<<< orphan*/  RSS_KEYLEN ; 
 int /*<<< orphan*/  RSS_TYPE_IPV4 ; 
 int /*<<< orphan*/  RSS_TYPE_IPV6 ; 
 int /*<<< orphan*/  RSS_TYPE_TCP_IPV4 ; 
 int /*<<< orphan*/  RSS_TYPE_TCP_IPV6 ; 
 int /*<<< orphan*/  RSS_TYPE_UDP_IPV4 ; 
 int /*<<< orphan*/  RSS_TYPE_UDP_IPV6 ; 
#define  SIOCADDMULTI 137 
#define  SIOCDELMULTI 136 
#define  SIOCGI2C 135 
#define  SIOCGIFMEDIA 134 
#define  SIOCGIFRSSHASH 133 
#define  SIOCGIFRSSKEY 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  VLAN_CAPABILITIES (struct ifnet*) ; 
 int copyin (int /*<<< orphan*/ ,struct ifi2creq*,int) ; 
 int copyout (struct ifi2creq*,int /*<<< orphan*/ ,int) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ifr_data_get_ptr (struct ifreq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int mlx4_en_change_mtu (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlx4_en_get_rss_key (struct mlx4_en_priv*,int /*<<< orphan*/ *) ; 
 int mlx4_en_get_rss_mask (struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_en_set_rx_mode (struct ifnet*) ; 
 int /*<<< orphan*/  mlx4_en_start_port (struct ifnet*) ; 
 int /*<<< orphan*/  mlx4_en_stop_port (struct ifnet*) ; 
 int mlx4_get_module_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx4_en_ioctl(struct ifnet *dev, u_long command, caddr_t data)
{
	struct mlx4_en_priv *priv;
	struct mlx4_en_dev *mdev;
	struct ifreq *ifr;
	int error;
	int mask;
	struct ifrsskey *ifrk;
	const u32 *key;
	struct ifrsshash *ifrh;
	u8 rss_mask;

	error = 0;
	mask = 0;
	priv = dev->if_softc;

	/* check if detaching */
	if (priv == NULL || priv->gone != 0)
		return (ENXIO);

	mdev = priv->mdev;
	ifr = (struct ifreq *) data;

	switch (command) {
	case SIOCSIFMTU:
		error = -mlx4_en_change_mtu(dev, ifr->ifr_mtu);
		break;
	case SIOCSIFFLAGS:
		if (dev->if_flags & IFF_UP) {
			if ((dev->if_drv_flags & IFF_DRV_RUNNING) == 0) {
				mutex_lock(&mdev->state_lock);
				mlx4_en_start_port(dev);
				mutex_unlock(&mdev->state_lock);
			} else {
				mlx4_en_set_rx_mode(dev);
			}
		} else {
			mutex_lock(&mdev->state_lock);
			if (dev->if_drv_flags & IFF_DRV_RUNNING) {
				mlx4_en_stop_port(dev);
				if_link_state_change(dev, LINK_STATE_DOWN);
			}
			mutex_unlock(&mdev->state_lock);
		}
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		mlx4_en_set_rx_mode(dev);
		break;
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		error = ifmedia_ioctl(dev, ifr, &priv->media, command);
		break;
	case SIOCSIFCAP:
		mutex_lock(&mdev->state_lock);
		mask = ifr->ifr_reqcap ^ dev->if_capenable;
		if (mask & IFCAP_TXCSUM) {
			dev->if_capenable ^= IFCAP_TXCSUM;
			dev->if_hwassist ^= (CSUM_TCP | CSUM_UDP | CSUM_IP);

			if (IFCAP_TSO4 & dev->if_capenable &&
			    !(IFCAP_TXCSUM & dev->if_capenable)) {
				dev->if_capenable &= ~IFCAP_TSO4;
				dev->if_hwassist &= ~CSUM_IP_TSO;
				if_printf(dev,
				    "tso4 disabled due to -txcsum.\n");
			}
		}
		if (mask & IFCAP_TXCSUM_IPV6) {
			dev->if_capenable ^= IFCAP_TXCSUM_IPV6;
			dev->if_hwassist ^= (CSUM_UDP_IPV6 | CSUM_TCP_IPV6);

			if (IFCAP_TSO6 & dev->if_capenable &&
			    !(IFCAP_TXCSUM_IPV6 & dev->if_capenable)) {
				dev->if_capenable &= ~IFCAP_TSO6;
				dev->if_hwassist &= ~CSUM_IP6_TSO;
				if_printf(dev,
				    "tso6 disabled due to -txcsum6.\n");
			}
		}
		if (mask & IFCAP_RXCSUM)
			dev->if_capenable ^= IFCAP_RXCSUM;
		if (mask & IFCAP_RXCSUM_IPV6)
			dev->if_capenable ^= IFCAP_RXCSUM_IPV6;

		if (mask & IFCAP_TSO4) {
			if (!(IFCAP_TSO4 & dev->if_capenable) &&
			    !(IFCAP_TXCSUM & dev->if_capenable)) {
				if_printf(dev, "enable txcsum first.\n");
				error = EAGAIN;
				goto out;
			}
			dev->if_capenable ^= IFCAP_TSO4;
			dev->if_hwassist ^= CSUM_IP_TSO;
		}
		if (mask & IFCAP_TSO6) {
			if (!(IFCAP_TSO6 & dev->if_capenable) &&
			    !(IFCAP_TXCSUM_IPV6 & dev->if_capenable)) {
				if_printf(dev, "enable txcsum6 first.\n");
				error = EAGAIN;
				goto out;
			}
			dev->if_capenable ^= IFCAP_TSO6;
			dev->if_hwassist ^= CSUM_IP6_TSO;
		}
		if (mask & IFCAP_LRO)
			dev->if_capenable ^= IFCAP_LRO;
		if (mask & IFCAP_VLAN_HWTAGGING)
			dev->if_capenable ^= IFCAP_VLAN_HWTAGGING;
		if (mask & IFCAP_VLAN_HWFILTER)
			dev->if_capenable ^= IFCAP_VLAN_HWFILTER;
		if (mask & IFCAP_WOL_MAGIC)
			dev->if_capenable ^= IFCAP_WOL_MAGIC;
		if (dev->if_drv_flags & IFF_DRV_RUNNING)
			mlx4_en_start_port(dev);
out:
		mutex_unlock(&mdev->state_lock);
		VLAN_CAPABILITIES(dev);
		break;
#if __FreeBSD_version >= 1100036
	case SIOCGI2C: {
		struct ifi2creq i2c;

		error = copyin(ifr_data_get_ptr(ifr), &i2c, sizeof(i2c));
		if (error)
			break;
		if (i2c.len > sizeof(i2c.data)) {
			error = EINVAL;
			break;
		}
		/*
		 * Note that we ignore i2c.addr here. The driver hardcodes
		 * the address to 0x50, while standard expects it to be 0xA0.
		 */
		error = mlx4_get_module_info(mdev->dev, priv->port,
		    i2c.offset, i2c.len, i2c.data);
		if (error < 0) {
			error = -error;
			break;
		}
		error = copyout(&i2c, ifr_data_get_ptr(ifr), sizeof(i2c));
		break;
	}
#endif
	case SIOCGIFRSSKEY:
		ifrk = (struct ifrsskey *)data;
		ifrk->ifrk_func = RSS_FUNC_TOEPLITZ;
		mutex_lock(&mdev->state_lock);
		key = mlx4_en_get_rss_key(priv, &ifrk->ifrk_keylen);
		if (ifrk->ifrk_keylen > RSS_KEYLEN)
			error = EINVAL;
		else
			memcpy(ifrk->ifrk_key, key, ifrk->ifrk_keylen);
		mutex_unlock(&mdev->state_lock);
		break;

	case SIOCGIFRSSHASH:
		mutex_lock(&mdev->state_lock);
		rss_mask = mlx4_en_get_rss_mask(priv);
		mutex_unlock(&mdev->state_lock);
		ifrh = (struct ifrsshash *)data;
		ifrh->ifrh_func = RSS_FUNC_TOEPLITZ;
		ifrh->ifrh_types = 0;
		if (rss_mask & MLX4_RSS_IPV4)
			ifrh->ifrh_types |= RSS_TYPE_IPV4;
		if (rss_mask & MLX4_RSS_TCP_IPV4)
			ifrh->ifrh_types |= RSS_TYPE_TCP_IPV4;
		if (rss_mask & MLX4_RSS_IPV6)
			ifrh->ifrh_types |= RSS_TYPE_IPV6;
		if (rss_mask & MLX4_RSS_TCP_IPV6)
			ifrh->ifrh_types |= RSS_TYPE_TCP_IPV6;
		if (rss_mask & MLX4_RSS_UDP_IPV4)
			ifrh->ifrh_types |= RSS_TYPE_UDP_IPV4;
		if (rss_mask & MLX4_RSS_UDP_IPV6)
			ifrh->ifrh_types |= RSS_TYPE_UDP_IPV6;
		break;

	default:
		error = ether_ioctl(dev, command, data);
		break;
	}

	return (error);
}