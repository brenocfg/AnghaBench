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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void emitload(int outfd, int reg, unsigned value)
{
	char buf[8] = {
		0x3c, 0x04 + reg,
		value >> 24, value >> 16,
		0x34, 0x84 + reg + (reg << 5),
		value >> 8, value,
	};
	if (write(outfd, buf, sizeof(buf)) != sizeof(buf)) {
		fprintf(stderr, "write: %s\n", strerror(errno));
		exit(1);
	}
}