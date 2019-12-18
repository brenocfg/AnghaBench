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
struct ata_eh_context {int /*<<< orphan*/  i; } ;
struct ata_link {struct ata_eh_context eh_context; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_eh_clear_action (struct ata_link*,struct ata_device*,int /*<<< orphan*/ *,unsigned int) ; 

void ata_eh_done(struct ata_link *link, struct ata_device *dev,
		 unsigned int action)
{
	struct ata_eh_context *ehc = &link->eh_context;

	ata_eh_clear_action(link, dev, &ehc->i, action);
}