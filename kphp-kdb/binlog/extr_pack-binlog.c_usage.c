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
 char* FullVersionStr ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void usage (void) {
  printf ("%s\n", FullVersionStr);
  printf (
    "pack-binlog [-123456789] [-u<username>] [-v] <binlog>\n"
    "\tBinlog packing tool.\n"
    "\t[-v]\t\toutput statistical and debug information into stderr\n"
    "\t[-d]\t\tdecompress\n"
    "\t[-c]\t\tdecompress to stdout\n"
    "\t[-t]\t\ttest, check the compressed file integrity\n"
    "\t[-i]\t\tshow zipped binlog info\n"
    "\t[-x]\t\txz compression\n"
    "\t[-z]\t\tzlib compression\n"
    "\t[-1]\t\tcompress faster\n"
    "\t[-6]\t\tdefault for xz\n"
    "\t[-9]\t\tcompress better (default for zlib)\n"
    "\t[-K]\t\tallows to cut KFS headers (not recommend to use).\n"
    "\t\t\tKFS headers cuttings leads to broken replication and failure during binlog replaying after unpacking.\n"
#ifdef BINLOG_ZIP_BZ2
    "\t[-j]\t\tbz2 compression\n"
#endif
  );
/*
  int i;
  for (i = 0; i < 10; i++) {
    long long x = lzma_easy_decoder_memusage (i);
    printf ("lzma_easy_decoder_memusage (%d) = %.3lfMi\n", i, x / (double) (1<<20));
  }
*/
  exit (2);
}