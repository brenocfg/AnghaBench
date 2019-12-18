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
 scalar_t__ convert ; 
 size_t convert_from_net (char*,int) ; 
 int /*<<< orphan*/  file ; 
 size_t fwrite (char*,int,int,int /*<<< orphan*/ ) ; 

size_t
write_file(char *buffer, int count)
{

	if (convert == 0)
		return fwrite(buffer, 1, count, file);

	return convert_from_net(buffer, count);
}