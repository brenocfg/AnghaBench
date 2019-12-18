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
 int /*<<< orphan*/  sprintf (char*,char*,int,char const*) ; 

__attribute__((used)) static char *
cfi_fmtsize(uint32_t sz)
{
	static char buf[8];
	static const char *sfx[] = { "", "K", "M", "G" };
	int sfxidx;

	sfxidx = 0;
	while (sfxidx < 3 && sz > 1023) {
		sz /= 1024;
		sfxidx++;
	}

	sprintf(buf, "%u%sB", sz, sfx[sfxidx]);
	return (buf);
}