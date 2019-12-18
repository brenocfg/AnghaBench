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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 char const* octeon_model_get_string_buffer (int /*<<< orphan*/ ,char*) ; 

const char *octeon_model_get_string(uint32_t chip_id)
{
    static char         buffer[32];
    return octeon_model_get_string_buffer(chip_id,buffer);
}