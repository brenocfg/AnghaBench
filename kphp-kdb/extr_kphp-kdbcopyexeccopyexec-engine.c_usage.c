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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void usage (void) {
  fprintf (stderr, "%s\n", FullVersionStr);
  fprintf (stderr, "Performs transactions from auxiliary binlog and writes results to the binlog.\n");
  fprintf (stderr,
           "./copyexec-engine -I<instance-mask> -T<tmp-dir> -P<public-key-prefix> [-R<host:port>] [-v] [-p<port>] [-b<backlog>] [-c<max-conn>] [-l<log-name>] -a<aux-binlog-name> <binlog>\n"
                   "\t-I<instance-mask>\tmandatory option, instance mask could be hex (prefix:'0x'), oct (prefix:'0') or dec\n"
                   "\t-P<public-key-prefix>\t(mandatory option), full public key name is concatenation of <public-key-prefix> and key_id found in aux binlog.\n"
                   "\t-T<tmp-dir>\ttemporary transaction files will be created in subdirs of given directory\n"
                   "\t-a<aux-binlog-name>\tshould be full binlog filename (mandatory option)\n"
                   "\t-E<volume-id>\tcreates new empty binlog, volume-id is a string.\n"
                   "\t\t\tFor creating new binlog also need specify public-key-prefix and aux-binlog-name (for finding and writing sync point to the main binlog).\n"
                   "\t-p<port>\tif port given when copyexec-engine will reply to the stats memcache command\n"
                   "\t-R<host:port>\tif given copyexec-engine will send results to the copyexec-results-engine\n"
                   "\t-v\tincrease verbosity level\n"
          );
  exit (2);
}