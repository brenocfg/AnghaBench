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
typedef  size_t ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 size_t ENODEV ; 
 int NVRAM_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * nvram_image ; 

__attribute__((used)) static ssize_t core99_nvram_read(char *buf, size_t count, loff_t *index)
{
	int i;

	if (nvram_image == NULL)
		return -ENODEV;
	if (*index > NVRAM_SIZE)
		return 0;

	i = *index;
	if (i + count > NVRAM_SIZE)
		count = NVRAM_SIZE - i;

	memcpy(buf, &nvram_image[i], count);
	*index = i + count;
	return count;
}