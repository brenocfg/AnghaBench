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
struct TYPE_2__ {size_t readsp; int /*<<< orphan*/ * readstack; } ;

/* Variables and functions */
#define  EOF 128 
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_string (int /*<<< orphan*/ *) ; 
 char readch () ; 
 int /*<<< orphan*/  readline () ; 
 int /*<<< orphan*/  readreg () ; 
 int /*<<< orphan*/  unreadch () ; 

__attribute__((used)) static void
skip_until_mark(void)
{

	for (;;) {
		switch (readch()) {
		case 'M':
			return;
		case EOF:
			errx(1, "mark not found");
			return;
		case 'l':
		case 'L':
		case 's':
		case 'S':
		case ':':
		case ';':
		case '<':
		case '>':
		case '=':
			readreg();
			if (readch() == 'e')
				readreg();
			else
				unreadch();
			break;
		case '[':
			free(read_string(&bmachine.readstack[bmachine.readsp]));
			break;
		case '!':
			switch (readch()) {
				case '<':
				case '>':
				case '=':
					readreg();
					if (readch() == 'e')
						readreg();
					else
						unreadch();
					break;
				default:
					free(readline());
					break;
			}
			break;
		default:
			break;
		}
	}
}