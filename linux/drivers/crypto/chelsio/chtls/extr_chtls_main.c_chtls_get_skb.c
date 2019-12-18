#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int dummy; } ;
struct chtls_dev {TYPE_1__* askb; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (TYPE_1__*,int) ; 
 int /*<<< orphan*/  skb_reset_transport_header (TYPE_1__*) ; 

__attribute__((used)) static int chtls_get_skb(struct chtls_dev *cdev)
{
	cdev->askb = alloc_skb(sizeof(struct tcphdr), GFP_KERNEL);
	if (!cdev->askb)
		return -ENOMEM;

	skb_put(cdev->askb, sizeof(struct tcphdr));
	skb_reset_transport_header(cdev->askb);
	memset(cdev->askb->data, 0, cdev->askb->len);
	return 0;
}