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
	printf("Checking TRX file:\n");
	printf("\totrx check <file> [options]\tcheck if file is a valid TRX\n");
	printf("\t-o offset\t\t\toffset of TRX data in file (default: 0)\n");
	printf("\n");
	printf("Creating new TRX file:\n");
	printf("\totrx create <file> [options] [partitions]\n");
	printf("\t-f file\t\t\t\t[partition] start new partition with content copied from file\n");
	printf("\t-A file\t\t\t\t[partition] append current partition with content copied from file\n");
	printf("\t-a alignment\t\t\t[partition] align current partition\n");
	printf("\t-b offset\t\t\t[partition] append zeros to partition till reaching absolute offset\n");
	printf("\n");
	printf("Extracting from TRX file:\n");
	printf("\totrx extract <file> [options]\textract partitions from TRX file\n");
	printf("\t-o offset\t\t\toffset of TRX data in file (default: 0)\n");
	printf("\t-1 file\t\t\t\tfile to extract 1st partition to (optional)\n");
	printf("\t-2 file\t\t\t\tfile to extract 2nd partition to (optional)\n");
	printf("\t-3 file\t\t\t\tfile to extract 3rd partition to (optional)\n");
}