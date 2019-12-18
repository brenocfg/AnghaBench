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
struct stat {int /*<<< orphan*/  st_mode; scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
#define  TYPE_A 130 
#define  TYPE_I 129 
#define  TYPE_L 128 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int /*<<< orphan*/  reply (int,char*,...) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int type ; 

__attribute__((used)) static void
sizecmd(char *filename)
{
	switch (type) {
	case TYPE_L:
	case TYPE_I: {
		struct stat stbuf;
		if (stat(filename, &stbuf) < 0 || !S_ISREG(stbuf.st_mode))
			reply(550, "%s: not a plain file.", filename);
		else
			reply(213, "%lu", (unsigned long)stbuf.st_size);
		break;
	}
	case TYPE_A: {
		FILE *fin;
		int c;
		size_t count;
		struct stat stbuf;
		fin = fopen(filename, "r");
		if (fin == NULL) {
			perror_reply(550, filename);
			return;
		}
		if (fstat(fileno(fin), &stbuf) < 0 || !S_ISREG(stbuf.st_mode)) {
			reply(550, "%s: not a plain file.", filename);
			fclose(fin);
			return;
		}

		count = 0;
		while((c=getc(fin)) != EOF) {
			if (c == '\n')	/* will get expanded to \r\n */
				count++;
			count++;
		}
		fclose(fin);

		reply(213, "%lu", (unsigned long)count);
		break;
	}
	default:
		reply(504, "SIZE not implemented for Type %c.", "?AEIL"[type]);
	}
}