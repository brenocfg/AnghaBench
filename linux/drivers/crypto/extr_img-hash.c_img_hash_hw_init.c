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
typedef  int u64 ;
typedef  unsigned long long u32 ;
struct img_hash_dev {int flags; int /*<<< orphan*/  dev; scalar_t__ err; TYPE_1__* req; } ;
struct TYPE_2__ {scalar_t__ nbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_INTENAB ; 
 unsigned long long CR_INT_NEW_RESULTS_SET ; 
 int /*<<< orphan*/  CR_MESSAGE_LENGTH_H ; 
 int /*<<< orphan*/  CR_MESSAGE_LENGTH_L ; 
 int /*<<< orphan*/  CR_RESET ; 
 unsigned long long CR_RESET_SET ; 
 unsigned long long CR_RESET_UNSET ; 
 int DRIVER_FLAGS_INIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  img_hash_write (struct img_hash_dev*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static int img_hash_hw_init(struct img_hash_dev *hdev)
{
	unsigned long long nbits;
	u32 u, l;

	img_hash_write(hdev, CR_RESET, CR_RESET_SET);
	img_hash_write(hdev, CR_RESET, CR_RESET_UNSET);
	img_hash_write(hdev, CR_INTENAB, CR_INT_NEW_RESULTS_SET);

	nbits = (u64)hdev->req->nbytes << 3;
	u = nbits >> 32;
	l = nbits;
	img_hash_write(hdev, CR_MESSAGE_LENGTH_H, u);
	img_hash_write(hdev, CR_MESSAGE_LENGTH_L, l);

	if (!(DRIVER_FLAGS_INIT & hdev->flags)) {
		hdev->flags |= DRIVER_FLAGS_INIT;
		hdev->err = 0;
	}
	dev_dbg(hdev->dev, "hw initialized, nbits: %llx\n", nbits);
	return 0;
}