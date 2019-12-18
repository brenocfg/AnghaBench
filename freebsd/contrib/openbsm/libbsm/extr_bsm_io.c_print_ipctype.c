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
typedef  int u_char ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AT_IPC_MSG ; 
 int AT_IPC_SEM ; 
 int AT_IPC_SHM ; 
 int AU_OFLAG_RAW ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
print_ipctype(FILE *fp, u_char type, int oflags)
{
	if (oflags & AU_OFLAG_RAW)
		fprintf(fp, "%u", type);
	else {
		if (type == AT_IPC_MSG)
			fprintf(fp, "Message IPC");
		else if (type == AT_IPC_SEM)
			fprintf(fp, "Semaphore IPC");
		else if (type == AT_IPC_SHM)
			fprintf(fp, "Shared Memory IPC");
		else
			fprintf(fp, "%u", type);
	}
}