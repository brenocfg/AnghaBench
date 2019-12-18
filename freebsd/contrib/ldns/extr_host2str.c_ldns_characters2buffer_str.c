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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*,unsigned int) ; 

__attribute__((used)) static void 
ldns_characters2buffer_str(ldns_buffer* output,
		size_t amount, const uint8_t* characters)
{
	uint8_t ch;
	while (amount > 0) {
		ch = *characters++;
		if (isprint((int)ch) || ch == '\t') {
			if (ch == '\"' || ch == '\\')
				ldns_buffer_printf(output, "\\%c", ch);
			else
				ldns_buffer_printf(output, "%c", ch);
		} else {
			ldns_buffer_printf(output, "\\%03u",
                                (unsigned)(uint8_t) ch);
		}
		amount--;
	}
}