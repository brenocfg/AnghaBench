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
struct board_info {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void usage(int status)
{
	FILE *stream = (status != EXIT_SUCCESS) ? stderr : stdout;
	struct board_info *board;

	fprintf(stream, "Usage: %s [OPTIONS...]\n", progname);
	fprintf(stream,
"\n"
"Options:\n"
"  -c              use combined kernel image\n"
"  -e              swap endianness in kernel load address and entry point\n"
"  -E <ep>         overwrite kernel entry point with <ep> (hexval prefixed with 0x)\n"
"  -L <la>         overwrite kernel load address with <la> (hexval prefixed with 0x)\n"
"  -H <hwid>       use hardware id specified with <hwid>\n"
"  -W <hwrev>      use hardware revision specified with <hwrev>\n"
"  -w <hwveradd>   use additional hardware version specified with <hwveradd>\n"
"  -F <id>         use flash layout specified with <id>\n"
"  -k <file>       read kernel image from the file <file>\n"
"  -r <file>       read rootfs image from the file <file>\n"
"  -a <align>      align the rootfs start on an <align> bytes boundary\n"
"  -R <offset>     overwrite rootfs offset with <offset> (hexval prefixed with 0x)\n"
"  -o <file>       write output to the file <file>\n"
"  -s              strip padding from the end of the image\n"
"  -j              add jffs2 end-of-filesystem markers\n"
"  -N <vendor>     set image vendor to <vendor>\n"
"  -T <version>    set header version to <version>\n"
"  -V <version>    set image version to <version>\n"
"  -v <version>    set firmware version to <version>\n"
"  -y <version>    set secondary version to <version>\n"
"  -i <file>       inspect given firmware file <file>\n"
"  -x              extract kernel and rootfs while inspecting (requires -i)\n"
"  -h              show this screen\n"
	);

	exit(status);
}