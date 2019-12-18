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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _IOFBF ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t) ; 

void
setbuffer(FILE *fp, char *buf, int size)
{

	(void)setvbuf(fp, buf, buf ? _IOFBF : _IONBF, (size_t)size);
}