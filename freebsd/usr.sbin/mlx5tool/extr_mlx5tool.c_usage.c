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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	fprintf(stderr,
	    "Usage: mlx5tool -d pci<d:b:s:f> [-w -o dump.file | -r |"
	    " -e | -f fw.mfa2 | -z]\n");
	fprintf(stderr, "\t-w - write firmware dump to the specified file\n");
	fprintf(stderr, "\t-r - reset dump\n");
	fprintf(stderr, "\t-E - get eeprom info\n");
	fprintf(stderr, "\t-e - force dump\n");
	fprintf(stderr, "\t-f fw.img - flash firmware from fw.img\n");
	fprintf(stderr, "\t-z - initiate firmware reset\n");
	exit(1);
}