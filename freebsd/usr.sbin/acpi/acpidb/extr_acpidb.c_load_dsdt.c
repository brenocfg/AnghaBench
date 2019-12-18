#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int Length; } ;
typedef  TYPE_1__ u_int8_t ;
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  filetmp ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_NEW_TABLE_DESC ;
typedef  int /*<<< orphan*/  ACPI_ADR_SPACE_HANDLER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_CMOS ; 
 int /*<<< orphan*/  ACPI_ADR_SPACE_EC ; 
 int /*<<< orphan*/  ACPI_ADR_SPACE_PCI_BAR_TARGET ; 
 int /*<<< orphan*/  ACPI_ADR_SPACE_PCI_CONFIG ; 
 int /*<<< orphan*/  ACPI_ADR_SPACE_SMBUS ; 
 int /*<<< orphan*/  ACPI_ADR_SPACE_SYSTEM_IO ; 
 int /*<<< orphan*/  ACPI_ADR_SPACE_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int AE_OK ; 
 int /*<<< orphan*/  AcGetAllTablesFromFile (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiDbUserCommands () ; 
 scalar_t__ AcpiGbl_DebuggerConfiguration ; 
 int /*<<< orphan*/  AcpiInitializeDebugger () ; 
 int AcpiInitializeSubsystem () ; 
 int AcpiInstallAddressSpaceHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PROT_READ ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ aml_vm_space_handler_cmos ; 
 scalar_t__ aml_vm_space_handler_ec ; 
 scalar_t__ aml_vm_space_handler_pci_bar_target ; 
 scalar_t__ aml_vm_space_handler_pci_config ; 
 scalar_t__ aml_vm_space_handler_smbus ; 
 scalar_t__ aml_vm_space_handler_system_io ; 
 scalar_t__ aml_vm_space_handler_system_memory ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ dummy_dsdt_table ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fstat (int,struct stat*) ; 
 TYPE_1__* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (TYPE_1__*,size_t) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  write (int,TYPE_1__*,int) ; 

__attribute__((used)) static int
load_dsdt(const char *dsdtfile)
{
	char			filetmp[PATH_MAX];
	ACPI_NEW_TABLE_DESC	*list;
	u_int8_t		*code;
	struct stat		sb;
	int			dounlink, error, fd;

	fd = open(dsdtfile, O_RDONLY, 0);
	if (fd == -1) {
		perror("open");
		return (-1);
	}
	if (fstat(fd, &sb) == -1) {
		perror("fstat");
		close(fd);
		return (-1);
	}
	code = mmap(NULL, (size_t)sb.st_size, PROT_READ, MAP_PRIVATE, fd, (off_t)0);
	close(fd);
	if (code == NULL) {
		perror("mmap");
		return (-1);
	}
	if ((error = AcpiInitializeSubsystem()) != AE_OK) {
		munmap(code, (size_t)sb.st_size);
		return (-1);
	}

	/*
	 * make sure DSDT data contains table header or not.
	 */
	if (strncmp((char *)code, "DSDT", 4) == 0) {
		dounlink = 0;
		strlcpy(filetmp, dsdtfile, sizeof(filetmp));
	} else {
		dounlink = 1;
		mode_t	mode = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dummy_dsdt_table.Length = sizeof(ACPI_TABLE_HEADER) + sb.st_size;
		if ((size_t)snprintf(filetmp, sizeof(filetmp), "%s.tmp",
		    dsdtfile) > sizeof(filetmp) - 1) {
			fprintf(stderr, "file name too long\n");
			munmap(code, (size_t)sb.st_size);
			return (-1);
		}
		fd = open(filetmp, O_WRONLY | O_CREAT | O_TRUNC, mode);
		if (fd == -1) {
			perror("open");
			munmap(code, (size_t)sb.st_size);
			return (-1);
		}
		write(fd, &dummy_dsdt_table, sizeof(ACPI_TABLE_HEADER));

		write(fd, code, sb.st_size);
		close(fd);
	}
	munmap(code, (size_t)sb.st_size);

	/*
	 * Install the virtual machine version of address space handlers.
	 */
	if ((error = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
			ACPI_ADR_SPACE_SYSTEM_MEMORY,
			(ACPI_ADR_SPACE_HANDLER)aml_vm_space_handler_system_memory,
			NULL, NULL)) != AE_OK) {
		fprintf(stderr, "could not initialise SystemMemory handler: %d\n", error);
		return (-1);
	}
	if ((error = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
			ACPI_ADR_SPACE_SYSTEM_IO,
			(ACPI_ADR_SPACE_HANDLER)aml_vm_space_handler_system_io,
			NULL, NULL)) != AE_OK) {
		fprintf(stderr, "could not initialise SystemIO handler: %d\n", error);
		return (-1);
	}
	if ((error = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
			ACPI_ADR_SPACE_PCI_CONFIG,
			(ACPI_ADR_SPACE_HANDLER)aml_vm_space_handler_pci_config,
			NULL, NULL)) != AE_OK) {
		fprintf(stderr, "could not initialise PciConfig handler: %d\n", error);
		return (-1);
	}
	if ((error = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
			ACPI_ADR_SPACE_EC,
			(ACPI_ADR_SPACE_HANDLER)aml_vm_space_handler_ec,
			NULL, NULL)) != AE_OK) {
		fprintf(stderr, "could not initialise EC handler: %d\n", error);
		return (-1);
	}
	if ((error = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
			ACPI_ADR_SPACE_SMBUS,
			(ACPI_ADR_SPACE_HANDLER)aml_vm_space_handler_smbus,
			NULL, NULL)) != AE_OK) {
		fprintf(stderr, "could not initialise SMBUS handler: %d\n", error);
		return (-1);
	}
	if ((error = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
			ACPI_ADR_SPACE_CMOS,
			(ACPI_ADR_SPACE_HANDLER)aml_vm_space_handler_cmos,
			NULL, NULL)) != AE_OK) {
		fprintf(stderr, "could not initialise CMOS handler: %d\n", error);
		return (-1);
	}
	if ((error = AcpiInstallAddressSpaceHandler(ACPI_ROOT_OBJECT,
			ACPI_ADR_SPACE_PCI_BAR_TARGET,
			(ACPI_ADR_SPACE_HANDLER)aml_vm_space_handler_pci_bar_target,
			NULL, NULL)) != AE_OK) {
		fprintf(stderr, "could not initialise PCI BAR TARGET handler: %d\n", error);
		return (-1);
	}

	list = NULL;
	AcGetAllTablesFromFile(filetmp, TRUE, &list);

	AcpiInitializeDebugger();
	AcpiGbl_DebuggerConfiguration = 0;
	AcpiDbUserCommands();

	if (dounlink) {
		unlink(filetmp);
	}

	return (0);
}