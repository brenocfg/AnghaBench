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
typedef  void* u16 ;
struct regmap_ibt_context {struct hci_dev* hdev; void* op_write; void* op_read; } ;
struct regmap {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct regmap* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,void*,void*) ; 
 struct regmap_ibt_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_ibt ; 
 int /*<<< orphan*/  regmap_ibt_cfg ; 
 struct regmap* regmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct regmap_ibt_context*,int /*<<< orphan*/ *) ; 

struct regmap *btintel_regmap_init(struct hci_dev *hdev, u16 opcode_read,
				   u16 opcode_write)
{
	struct regmap_ibt_context *ctx;

	bt_dev_info(hdev, "regmap: Init R%x-W%x region", opcode_read,
		    opcode_write);

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	ctx->op_read = opcode_read;
	ctx->op_write = opcode_write;
	ctx->hdev = hdev;

	return regmap_init(&hdev->dev, &regmap_ibt, ctx, &regmap_ibt_cfg);
}