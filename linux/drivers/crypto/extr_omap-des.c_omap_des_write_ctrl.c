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
typedef  int u32 ;
struct omap_des_dev {int flags; TYPE_2__* req; TYPE_1__* ctx; } ;
struct TYPE_4__ {scalar_t__ info; } ;
struct TYPE_3__ {int keylen; int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 int /*<<< orphan*/  DES_REG_CTRL (struct omap_des_dev*) ; 
 int DES_REG_CTRL_CBC ; 
 int DES_REG_CTRL_DIRECTION ; 
 int DES_REG_CTRL_TDES ; 
 int /*<<< orphan*/  DES_REG_IV (struct omap_des_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DES_REG_KEY (struct omap_des_dev*,int) ; 
 int FLAGS_CBC ; 
 int FLAGS_ENCRYPT ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int omap_des_hw_init (struct omap_des_dev*) ; 
 int /*<<< orphan*/  omap_des_write (struct omap_des_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_des_write_mask (struct omap_des_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  omap_des_write_n (struct omap_des_dev*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int omap_des_write_ctrl(struct omap_des_dev *dd)
{
	unsigned int key32;
	int i, err;
	u32 val = 0, mask = 0;

	err = omap_des_hw_init(dd);
	if (err)
		return err;

	key32 = dd->ctx->keylen / sizeof(u32);

	/* it seems a key should always be set even if it has not changed */
	for (i = 0; i < key32; i++) {
		omap_des_write(dd, DES_REG_KEY(dd, i),
			       __le32_to_cpu(dd->ctx->key[i]));
	}

	if ((dd->flags & FLAGS_CBC) && dd->req->info)
		omap_des_write_n(dd, DES_REG_IV(dd, 0), dd->req->info, 2);

	if (dd->flags & FLAGS_CBC)
		val |= DES_REG_CTRL_CBC;
	if (dd->flags & FLAGS_ENCRYPT)
		val |= DES_REG_CTRL_DIRECTION;
	if (key32 == 6)
		val |= DES_REG_CTRL_TDES;

	mask |= DES_REG_CTRL_CBC | DES_REG_CTRL_DIRECTION | DES_REG_CTRL_TDES;

	omap_des_write_mask(dd, DES_REG_CTRL(dd), val, mask);

	return 0;
}