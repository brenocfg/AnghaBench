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
typedef  int /*<<< orphan*/  uintmax_t ;
struct s_spcl {int const c_type; long c_count; scalar_t__* c_addr; int c_inumber; scalar_t__ c_firstrec; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int ino_t ;

/* Variables and functions */
#define  TS_ADDR 132 
#define  TS_BITS 131 
#define  TS_CLRI 130 
#define  TS_END 129 
#define  TS_INODE 128 
 int const TS_TAPE ; 
 int blksread ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ readmapflag ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
accthdr(struct s_spcl *header)
{
	static ino_t previno = 0x7fffffff;
	static int prevtype;
	static long predict;
	long blks, i;

	if (header->c_type == TS_TAPE) {
		fprintf(stderr, "Volume header ");
 		if (header->c_firstrec)
 			fprintf(stderr, "begins with record %jd",
			    (intmax_t)header->c_firstrec);
 		fprintf(stderr, "\n");
		previno = 0x7fffffff;
		return;
	}
	if (previno == 0x7fffffff)
		goto newcalc;
	switch (prevtype) {
	case TS_BITS:
		fprintf(stderr, "Dumped inodes map header");
		break;
	case TS_CLRI:
		fprintf(stderr, "Used inodes map header");
		break;
	case TS_INODE:
		fprintf(stderr, "File header, ino %ju", (uintmax_t)previno);
		break;
	case TS_ADDR:
		fprintf(stderr, "File continuation header, ino %ju",
		    (uintmax_t)previno);
		break;
	case TS_END:
		fprintf(stderr, "End of tape header");
		break;
	}
	if (predict != blksread - 1)
		fprintf(stderr, "; predicted %ld blocks, got %ld blocks",
			predict, blksread - 1);
	fprintf(stderr, "\n");
newcalc:
	blks = 0;
	if (header->c_type != TS_END)
		for (i = 0; i < header->c_count; i++)
			if (readmapflag || header->c_addr[i] != 0)
				blks++;
	predict = blks;
	blksread = 0;
	prevtype = header->c_type;
	previno = header->c_inumber;
}