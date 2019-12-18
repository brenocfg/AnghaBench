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
struct cpx_board {char* model; char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 struct cpx_board* boards ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

void
usage(int status)
{
	FILE *stream = (status != EXIT_SUCCESS) ? stderr : stdout;
	struct cpx_board *board;

	fprintf(stream, "Usage: %s [OPTION...] <file>\n", progname);
	fprintf(stream,
"\n"
"  <file>          write output to the <file>\n"
"\n"
"Options:\n"
"  -B <board>      create firmware for the board specified with <board>.\n"
"                  This option set vendor id, device id, subvendor id,\n"
"                  subdevice id, and flash size options to the right value.\n"
"                  valid <board> values:\n");
	for (board = boards; board->model != NULL; board++){
		fprintf(stream,
"                      %-12s: %s\n",
		 board->model, board->name);
	};
	fprintf(stream,
"  -i <vid>:<did>[:<svid>[:<sdid>]]\n"
"                  create firmware for board with vendor id <vid>, device\n"
"                  id <did>, subvendor id <svid> and subdevice id <sdid>.\n"
"  -r <rev>        set board revision to <rev>.\n"
"  -s <size>       set flash size to <size>\n"
"  -b <addr>:<len>[:[<flags>]:<file>]\n"
"                  define block at <addr> with length of <len>.\n"
"                  valid <flag> values:\n"
"                      h : add crc header before the file data.\n"
"  -p <addr>:<len>[:<flags>[:<param>[:<name>[:<file>]]]]\n"
"                  add partition at <addr>, with size of <len> to the\n"
"                  partition table, set partition name to <name>, partition \n"
"                  flags to <flags> and partition parameter to <param>.\n"
"                  If the <file> is specified content of the file will be \n"
"                  added to the firmware image.\n"
"                  valid <flag> values:\n"
"                      a:  this is the active partition. The bootloader loads\n"
"                          the firmware from this partition.\n"
"                      h:  the partition data have a header.\n"
"                      l:  the partition data uses LZMA compression.\n"
"                      p:  the bootloader loads data from this partition to\n"
"                          the RAM before decompress it.\n"
"  -h              show this screen\n"
	);

	exit(status);
}