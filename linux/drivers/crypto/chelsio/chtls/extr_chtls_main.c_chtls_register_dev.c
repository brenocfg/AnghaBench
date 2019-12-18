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
struct tls_device {int /*<<< orphan*/  kref; int /*<<< orphan*/  release; int /*<<< orphan*/  unhash; int /*<<< orphan*/  hash; int /*<<< orphan*/  feature; int /*<<< orphan*/  name; } ;
struct chtls_dev {int /*<<< orphan*/  cdev_state; TYPE_2__* lldi; struct tls_device tlsdev; } ;
struct TYPE_4__ {TYPE_1__** ports; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHTLS_CDEV_STATE_UP ; 
 int /*<<< orphan*/  TLS_DEVICE_NAME_MAX ; 
 int /*<<< orphan*/  chtls_create_hash ; 
 int /*<<< orphan*/  chtls_destroy_hash ; 
 int /*<<< orphan*/  chtls_dev_release ; 
 int /*<<< orphan*/  chtls_inline_feature ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_register_device (struct tls_device*) ; 

__attribute__((used)) static void chtls_register_dev(struct chtls_dev *cdev)
{
	struct tls_device *tlsdev = &cdev->tlsdev;

	strlcpy(tlsdev->name, "chtls", TLS_DEVICE_NAME_MAX);
	strlcat(tlsdev->name, cdev->lldi->ports[0]->name,
		TLS_DEVICE_NAME_MAX);
	tlsdev->feature = chtls_inline_feature;
	tlsdev->hash = chtls_create_hash;
	tlsdev->unhash = chtls_destroy_hash;
	tlsdev->release = chtls_dev_release;
	kref_init(&tlsdev->kref);
	tls_register_device(tlsdev);
	cdev->cdev_state = CHTLS_CDEV_STATE_UP;
}