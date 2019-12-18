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
 unsigned long L1_CACHE_BYTES ; 
 int /*<<< orphan*/  __delay (int) ; 
 scalar_t__ adrs ; 
 int /*<<< orphan*/  bus_error_jmp ; 
 int catch_memory_errors ; 
 int /*<<< orphan*/  cflush (void*) ; 
 int /*<<< orphan*/  cinval (void*) ; 
 int inchar () ; 
 int /*<<< orphan*/  scanhex (unsigned long*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 
 char termch ; 

__attribute__((used)) static void cacheflush(void)
{
	int cmd;
	unsigned long nflush;

	cmd = inchar();
	if (cmd != 'i')
		termch = cmd;
	scanhex((void *)&adrs);
	if (termch != '\n')
		termch = 0;
	nflush = 1;
	scanhex(&nflush);
	nflush = (nflush + L1_CACHE_BYTES - 1) / L1_CACHE_BYTES;
	if (setjmp(bus_error_jmp) == 0) {
		catch_memory_errors = 1;
		sync();

		if (cmd != 'i') {
			for (; nflush > 0; --nflush, adrs += L1_CACHE_BYTES)
				cflush((void *) adrs);
		} else {
			for (; nflush > 0; --nflush, adrs += L1_CACHE_BYTES)
				cinval((void *) adrs);
		}
		sync();
		/* wait a little while to see if we get a machine check */
		__delay(200);
	}
	catch_memory_errors = 0;
}