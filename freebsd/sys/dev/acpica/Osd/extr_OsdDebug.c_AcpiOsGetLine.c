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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ db_readline (char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

ACPI_STATUS
AcpiOsGetLine(char *Buffer, UINT32 BufferLength, UINT32 *BytesRead)
{
#ifdef DDB
	char *cp;

	cp = Buffer;
	if (db_readline(Buffer, BufferLength) > 0)
		while (*cp != '\0' && *cp != '\n' && *cp != '\r')
			cp++;
	*cp = '\0';
	if (BytesRead != NULL)
		*BytesRead = cp - Buffer;
	return (AE_OK);
#else
	printf("AcpiOsGetLine called but no input support");
	return (AE_NOT_EXIST);
#endif /* DDB */
}