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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
pci_fbuf_usage(char *opt)
{

	fprintf(stderr, "Invalid fbuf emulation option \"%s\"\r\n", opt);
	fprintf(stderr, "fbuf: {wait,}{vga=on|io|off,}rfb=<ip>:port"
	    "{,w=width}{,h=height}\r\n");
}