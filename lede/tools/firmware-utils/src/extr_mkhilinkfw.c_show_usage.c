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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void show_usage(const char *arg0)
{
	fprintf(stderr, "usage: %s -d|-e [-i FILE] [-o FILE]\n\n", arg0);
	fprintf(stderr, "%-15s %s\n", "-d, --decrypt", "decrypt data");
	fprintf(stderr, "%-15s %s\n", "-e, --encrypt", "encrypt data");
	fprintf(stderr, "%-15s %s\n", "-i, --input", "intput file (defaults to stdin)");
	fprintf(stderr, "%-15s %s\n", "-o, --output", "output file (defaults to stdout)");
	exit(-1);
}