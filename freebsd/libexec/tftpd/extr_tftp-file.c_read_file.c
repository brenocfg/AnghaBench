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
 size_t convert_to_net (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ ) ; 

size_t
read_file(char *buffer, int count)
{

	if (convert == 0)
		return fread(buffer, 1, count, file);

	return convert_to_net(buffer, count, 0);
}