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
typedef  int /*<<< orphan*/  snd_info_t ;

/* Variables and functions */
 void* S_CodecGetSound (char const*,int /*<<< orphan*/ *) ; 

void *S_CodecLoad(const char *filename, snd_info_t *info)
{
	return S_CodecGetSound(filename, info);
}