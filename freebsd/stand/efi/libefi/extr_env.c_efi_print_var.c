#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ UINTN ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_2__ {scalar_t__ (* GetVariable ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,char*) ;} ;
typedef  scalar_t__ EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_GUID ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 int CMD_WARN ; 
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 int EFI_ERROR_CODE (scalar_t__) ; 
 char* EFI_MEMORY_TYPE_INFORMATION_VARIABLE_NAME ; 
 scalar_t__ EFI_SUCCESS ; 
 char* MTC_VARIABLE_NAME ; 
 TYPE_1__* RS ; 
 int efi_guid_to_name (int /*<<< orphan*/ *,char**) ; 
 int efi_print_freebsd (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int efi_print_global (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int efi_print_mem_type (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int efi_print_other_value (char*,scalar_t__) ; 
 int efi_print_shell_str (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  efi_print_var_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ pager_output (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,char*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,char*) ; 

__attribute__((used)) static int
efi_print_var(CHAR16 *varnamearg, EFI_GUID *matchguid, int lflag)
{
	UINTN		datasz;
	EFI_STATUS	status;
	UINT32		attr;
	char		*str;
	uint8_t		*data;
	int		rv = CMD_OK;

	str = NULL;
	datasz = 0;
	status = RS->GetVariable(varnamearg, matchguid, &attr, &datasz, NULL);
	if (status != EFI_BUFFER_TOO_SMALL) {
		printf("Can't get the variable: error %#lx\n",
		    EFI_ERROR_CODE(status));
		return (CMD_ERROR);
	}
	data = malloc(datasz);
	if (data == NULL) {
		printf("Out of memory\n");
		return (CMD_ERROR);
	}

	status = RS->GetVariable(varnamearg, matchguid, &attr, &datasz, data);
	if (status != EFI_SUCCESS) {
		printf("Can't get the variable: error %#lx\n",
		    EFI_ERROR_CODE(status));
		free(data);
		return (CMD_ERROR);
	}

	if (efi_guid_to_name(matchguid, &str) == false) {
		rv = CMD_ERROR;
		goto done;
	}
	printf("%s ", str);
	efi_print_var_attr(attr);
	printf(" %S", varnamearg);

	if (lflag == 0) {
		if (strcmp(str, "global") == 0)
			rv = efi_print_global(varnamearg, data, datasz);
		else if (strcmp(str, "freebsd") == 0)
			rv = efi_print_freebsd(varnamearg, data, datasz);
		else if (strcmp(str,
		    EFI_MEMORY_TYPE_INFORMATION_VARIABLE_NAME) == 0)
			rv = efi_print_mem_type(varnamearg, data, datasz);
		else if (strcmp(str,
		    "47c7b227-c42a-11d2-8e57-00a0c969723b") == 0)
			rv = efi_print_shell_str(varnamearg, data, datasz);
		else if (strcmp(str, MTC_VARIABLE_NAME) == 0) {
			printf(" = ");
			printf("%u", *((uint32_t *)data));	/* UINT32 */
			rv = CMD_OK;
			if (pager_output("\n"))
				rv = CMD_WARN;
		} else
			rv = efi_print_other_value(data, datasz);
	} else if (pager_output("\n"))
		rv =  CMD_WARN;

done:
	free(str);
	free(data);
	return (rv);
}