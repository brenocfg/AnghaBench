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
struct TYPE_4__ {TYPE_1__* esre1; } ;
struct esre_entry {TYPE_2__ esre; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  fw_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  efi_guid_to_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t fw_class_show(struct esre_entry *entry, char *buf)
{
	char *str = buf;

	efi_guid_to_str(&entry->esre.esre1->fw_class, str);
	str += strlen(str);
	str += sprintf(str, "\n");

	return str - buf;
}