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
struct fw_address_handler {unsigned long long offset; unsigned long long length; } ;

/* Variables and functions */

__attribute__((used)) static bool is_enclosing_handler(struct fw_address_handler *handler,
				 unsigned long long offset, size_t length)
{
	return handler->offset <= offset &&
		offset + length <= handler->offset + handler->length;
}