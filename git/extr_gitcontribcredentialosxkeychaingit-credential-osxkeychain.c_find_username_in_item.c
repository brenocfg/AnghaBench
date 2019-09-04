#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; int /*<<< orphan*/  tag; } ;
struct TYPE_5__ {int count; TYPE_2__* attr; } ;
typedef  int /*<<< orphan*/  SecKeychainItemRef ;
typedef  TYPE_1__ SecKeychainAttributeList ;
typedef  TYPE_2__ SecKeychainAttribute ;

/* Variables and functions */
 scalar_t__ SecKeychainItemCopyContent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SecKeychainItemFreeContent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kSecAccountItemAttr ; 
 int /*<<< orphan*/  write_item (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_username_in_item(SecKeychainItemRef item)
{
	SecKeychainAttributeList list;
	SecKeychainAttribute attr;

	list.count = 1;
	list.attr = &attr;
	attr.tag = kSecAccountItemAttr;

	if (SecKeychainItemCopyContent(item, NULL, &list, NULL, NULL))
		return;

	write_item("username", attr.data, attr.length);
	SecKeychainItemFreeContent(&list, NULL);
}