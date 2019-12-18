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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage() {
	printf("Usage:\n");
	printf("\n");
	printf("Info about SafeLoader:\n");
	printf("\tosafeloader info <file>\n");
	printf("\n");
	printf("Extract from SafeLoader:\n");
	printf("\tosafeloader extract <file> [options]\n");
	printf("\t-p name\t\t\t\tname of partition to extract\n");
	printf("\t-o file\t\t\t\toutput file\n");
}