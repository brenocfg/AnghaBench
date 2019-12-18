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
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;
struct TYPE_2__ {int /*<<< orphan*/  text_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  efi_call_proto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* efi_early ; 
 int /*<<< orphan*/  efi_simple_text_output_protocol ; 
 int /*<<< orphan*/  output_string ; 

void efi_char16_printk(efi_system_table_t *table, efi_char16_t *str)
{
	efi_call_proto(efi_simple_text_output_protocol, output_string,
		       efi_early->text_output, str);
}