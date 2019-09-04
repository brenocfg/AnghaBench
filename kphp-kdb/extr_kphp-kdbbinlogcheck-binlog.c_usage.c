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
 int /*<<< orphan*/  BACKUP_ALL_SUBOPTIONS ; 
 char* FullVersionStr ; 
 char* KFS_BINLOG_ZIP_CHUNK_SIZE ; 
 int /*<<< orphan*/  exit (int) ; 
 int heap_memory ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void usage (void) {
  printf ("%s\n", FullVersionStr);
  printf (
    "check-binlog [-u<username>] [-c<max-conn>] [-v] [-b<backups_dir>] [-a<binlog-name>] <binlog>\n"
    "\tChecking binlog tool.\n"
    "\t[-v]\t\toutput statistical and debug information into stderr\n"
    "\t[-s<N>]\tlimit disk reading speed to N bytes in second, e.g. 32m, N > 1g means no limit\n"
    "\t[-q]\tquick test (only slice sizes and rotation consistency check)\n"
    "\t[-H<heap-size>]\tdefines maximum heap size (default: %lld bytes).\n"
    "\t[-I<buffsize>]\tset IO buffer size (default buffsize is 16Mb)\n"
    "\t\tfor bin.bz files buffsize is equal to KFS_BINLOG_ZIP_CHUNK_SIZE (%d bytes)\n"
    "\t[-i]\tdisable check that snapshot is readable in the case removed first binlog file, \n"
    "\t\tNOTICE: snapshot heuristics doesn't work in the case of news-engine, ...\n"
    "\t[-k]\t\tkeep going on fatal errors\n"
    "\t[-E<N>]\tshow only first <N> errors for each binlog\n"
    "\t[-S]\tbackups have same names as original binlogs (no suffix with dot and 10 digits), check storage-engine volumes\n"
    "\t[-A]\tallow first available slice starts from LEV_ROTATE_FROM (Example: adstat).\n"
    "\t[-b<backups_dir>]\tset backups dir\n"
    "\t[-B<backups_suboptions>]\tset backups suboptions\n"
    "Backup suboptions:\n"
    "\t'p'\tpartial check, warning in the case no correct backup\n"
    "\t'P'\tpartial check, error in the case no correct backup\n"
    "\t'f'\tfull check, warning in the case no correct backup\n"
    "\t'F'\tfull check, error in the case no correct backup\n"
    "\t'd'\twarn if there is incorrect backup and at least one correct backup\n"
    "\t'r'\twarn if there is multiple correct backups\n"
    "\t'm'\twarn shorter backup for not last binlog file\n"
    "\t'M'\terror shorter backup for not last binlog file\n"
    "\t'l'\twarn shorter backup for last binlog file\n"
    "\t'L'\terror shorter backup for last binlog file\n"
    "Specifying backups suboptions as 'all' is equivalent to '%s'.\n",
    heap_memory,
    KFS_BINLOG_ZIP_CHUNK_SIZE,
    BACKUP_ALL_SUBOPTIONS
  );
  printf ("\n$./check-binlog -m <src1.bin> <src2.bin>\n"
    "\tOnly rotate logevents consistency check.\n");
  exit (2);
}