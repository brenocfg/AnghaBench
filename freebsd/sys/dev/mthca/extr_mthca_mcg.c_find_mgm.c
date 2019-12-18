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
struct mthca_mgm {int /*<<< orphan*/  next_gid_index; int /*<<< orphan*/  gid; } ;
typedef  struct mthca_mgm u8 ;
typedef  int u16 ;
struct mthca_mailbox {struct mthca_mgm* buf; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,struct mthca_mgm*,int) ; 
 int /*<<< orphan*/  memcpy (struct mthca_mgm*,struct mthca_mgm*,int) ; 
 int mthca_MGID_HASH (struct mthca_dev*,struct mthca_mailbox*,int*) ; 
 int mthca_READ_MGM (struct mthca_dev*,int,struct mthca_mailbox*) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,struct mthca_mgm*,int) ; 
 int /*<<< orphan*/  mthca_err (struct mthca_dev*,char*,...) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 
 struct mthca_mgm* zero_gid ; 

__attribute__((used)) static int find_mgm(struct mthca_dev *dev,
		    u8 *gid, struct mthca_mailbox *mgm_mailbox,
		    u16 *hash, int *prev, int *index)
{
	struct mthca_mailbox *mailbox;
	struct mthca_mgm *mgm = mgm_mailbox->buf;
	u8 *mgid;
	int err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return -ENOMEM;
	mgid = mailbox->buf;

	memcpy(mgid, gid, 16);

	err = mthca_MGID_HASH(dev, mailbox, hash);
	if (err) {
		mthca_err(dev, "MGID_HASH failed (%d)\n", err);
		goto out;
	}

	if (0)
		mthca_dbg(dev, "Hash for %pI6 is %04x\n", gid, *hash);

	*index = *hash;
	*prev  = -1;

	do {
		err = mthca_READ_MGM(dev, *index, mgm_mailbox);
		if (err) {
			mthca_err(dev, "READ_MGM failed (%d)\n", err);
			goto out;
		}

		if (!memcmp(mgm->gid, zero_gid, 16)) {
			if (*index != *hash) {
				mthca_err(dev, "Found zero MGID in AMGM.\n");
				err = -EINVAL;
			}
			goto out;
		}

		if (!memcmp(mgm->gid, gid, 16))
			goto out;

		*prev = *index;
		*index = be32_to_cpu(mgm->next_gid_index) >> 6;
	} while (*index);

	*index = -1;

 out:
	mthca_free_mailbox(dev, mailbox);
	return err;
}