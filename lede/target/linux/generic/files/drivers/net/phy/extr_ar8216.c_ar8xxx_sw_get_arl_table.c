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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {char* s; } ;
struct switch_val {int len; TYPE_2__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct mii_bus {int /*<<< orphan*/  mdio_lock; } ;
struct arl_entry {int* mac; int portmap; } ;
struct TYPE_3__ {int ports; } ;
struct ar8xxx_priv {char* arl_buf; int /*<<< orphan*/  reg_mutex; struct arl_entry* arl_table; TYPE_1__ dev; struct ar8xxx_chip* chip; struct mii_bus* mii_bus; } ;
struct ar8xxx_chip {int /*<<< orphan*/  (* get_arl_entry ) (struct ar8xxx_priv*,struct arl_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AR8XXX_ARL_GET_NEXT ; 
 int /*<<< orphan*/  AR8XXX_ARL_INITIALIZE ; 
 int AR8XXX_NUM_ARL_RECORDS ; 
 int BIT (int) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct ar8xxx_priv*,struct arl_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ar8xxx_priv*,struct arl_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ar8xxx_priv* swdev_to_ar8xxx (struct switch_dev*) ; 

int
ar8xxx_sw_get_arl_table(struct switch_dev *dev,
			const struct switch_attr *attr,
			struct switch_val *val)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	struct mii_bus *bus = priv->mii_bus;
	const struct ar8xxx_chip *chip = priv->chip;
	char *buf = priv->arl_buf;
	int i, j, k, len = 0;
	struct arl_entry *a, *a1;
	u32 status;

	if (!chip->get_arl_entry)
		return -EOPNOTSUPP;

	mutex_lock(&priv->reg_mutex);
	mutex_lock(&bus->mdio_lock);

	chip->get_arl_entry(priv, NULL, NULL, AR8XXX_ARL_INITIALIZE);

	for(i = 0; i < AR8XXX_NUM_ARL_RECORDS; ++i) {
		a = &priv->arl_table[i];
		duplicate:
		chip->get_arl_entry(priv, a, &status, AR8XXX_ARL_GET_NEXT);

		if (!status)
			break;

		/* avoid duplicates
		 * ARL table can include multiple valid entries
		 * per MAC, just with differing status codes
		 */
		for (j = 0; j < i; ++j) {
			a1 = &priv->arl_table[j];
			if (!memcmp(a->mac, a1->mac, sizeof(a->mac))) {
				/* ignore ports already seen in former entry */
				a->portmap &= ~a1->portmap;
				if (!a->portmap)
					goto duplicate;
			}
		}
	}

	mutex_unlock(&bus->mdio_lock);

	len += snprintf(buf + len, sizeof(priv->arl_buf) - len,
                        "address resolution table\n");

	if (i == AR8XXX_NUM_ARL_RECORDS)
		len += snprintf(buf + len, sizeof(priv->arl_buf) - len,
				"Too many entries found, displaying the first %d only!\n",
				AR8XXX_NUM_ARL_RECORDS);

	for (j = 0; j < priv->dev.ports; ++j) {
		for (k = 0; k < i; ++k) {
			a = &priv->arl_table[k];
			if (!(a->portmap & BIT(j)))
				continue;
			len += snprintf(buf + len, sizeof(priv->arl_buf) - len,
					"Port %d: MAC %02x:%02x:%02x:%02x:%02x:%02x\n",
					j,
					a->mac[5], a->mac[4], a->mac[3],
					a->mac[2], a->mac[1], a->mac[0]);
		}
	}

	val->value.s = buf;
	val->len = len;

	mutex_unlock(&priv->reg_mutex);

	return 0;
}