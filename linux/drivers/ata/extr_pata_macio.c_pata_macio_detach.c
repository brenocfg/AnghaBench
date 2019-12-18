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
struct pata_macio_priv {TYPE_2__* mdev; TYPE_1__* host; } ;
struct macio_dev {int dummy; } ;
struct ata_host {struct pata_macio_priv* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  media_bay; } ;
struct TYPE_3__ {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_host_detach (struct ata_host*) ; 
 int /*<<< orphan*/  lock_media_bay (int /*<<< orphan*/ ) ; 
 struct ata_host* macio_get_drvdata (struct macio_dev*) ; 
 int /*<<< orphan*/  unlock_media_bay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pata_macio_detach(struct macio_dev *mdev)
{
	struct ata_host *host = macio_get_drvdata(mdev);
	struct pata_macio_priv *priv = host->private_data;

	lock_media_bay(priv->mdev->media_bay);

	/* Make sure the mediabay callback doesn't try to access
	 * dead stuff
	 */
	priv->host->private_data = NULL;

	ata_host_detach(host);

	unlock_media_bay(priv->mdev->media_bay);

	return 0;
}