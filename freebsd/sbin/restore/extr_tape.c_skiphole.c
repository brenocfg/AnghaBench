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
 int MAXBSIZE ; 
 void stub1 (char*,size_t) ; 

__attribute__((used)) static void
skiphole(void (*skip)(char *, size_t), size_t *seekpos)
{
	char buf[MAXBSIZE];

	if (*seekpos > 0) {
		(*skip)(buf, *seekpos);
		*seekpos = 0;
	}
}