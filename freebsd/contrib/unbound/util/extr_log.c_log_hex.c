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

/* Variables and functions */
 int /*<<< orphan*/  log_hex_f (int /*<<< orphan*/ ,char const*,void*,size_t) ; 
 int /*<<< orphan*/  verbosity ; 

void 
log_hex(const char* msg, void* data, size_t length)
{
	log_hex_f(verbosity, msg, data, length);
}