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
typedef  int uint32_t ;

/* Variables and functions */
 int bsd_get_if_media (void*) ; 
 scalar_t__ bsd_set_if_media (void*,int) ; 

__attribute__((used)) static int
bsd_set_mediaopt(void *priv, uint32_t mask, uint32_t mode)
{
	int media = bsd_get_if_media(priv);

	if (media < 0)
		return -1;
	media &= ~mask;
	media |= mode;
	if (bsd_set_if_media(priv, media) < 0)
		return -1;
	return 0;
}