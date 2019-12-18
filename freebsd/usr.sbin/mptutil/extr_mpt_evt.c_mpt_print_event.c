#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int LogSequence; int TimeStamp; int LogEntryQualifier; int* LogData; } ;
typedef  TYPE_1__ MPI_LOG_0_ENTRY ;

/* Variables and functions */
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
mpt_print_event(MPI_LOG_0_ENTRY *entry, int verbose)
{
	int i;

	printf("%5d %7ds %4x ", entry->LogSequence, entry->TimeStamp,
	    entry->LogEntryQualifier);
	for (i = 0; i < 14; i++)
		printf("%02x ", entry->LogData[i]);
	printf("|");
	for (i = 0; i < 14; i++)
		printf("%c", isprint(entry->LogData[i]) ? entry->LogData[i] :
		    '.');
	printf("|\n");
	printf("                    ");
	for (i = 0; i < 14; i++)
		printf("%02x ", entry->LogData[i + 14]);
	printf("|");
	for (i = 0; i < 14; i++)
		printf("%c", isprint(entry->LogData[i + 14]) ?
		    entry->LogData[i + 14] : '.');
	printf("|\n");
}