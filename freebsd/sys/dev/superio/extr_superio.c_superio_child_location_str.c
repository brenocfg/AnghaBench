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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 int superio_get_ldn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
superio_child_location_str(device_t parent, device_t child, char *buf,
    size_t buflen)
{
	uint8_t ldn;

	ldn = superio_get_ldn(child);
	snprintf(buf, buflen, "ldn=0x%02x", ldn);
	return (0);
}