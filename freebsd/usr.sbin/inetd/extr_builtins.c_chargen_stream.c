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
typedef  int /*<<< orphan*/  text ;
struct servtab {int /*<<< orphan*/  se_service; } ;

/* Variables and functions */
 int LINESIZ ; 
 char* endring ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inetd_setproctitle (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  initring () ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* ring ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
chargen_stream(int s, struct servtab *sep)
{
	int len;
	char *rs, text[LINESIZ+2];

	inetd_setproctitle(sep->se_service, s);

	if (!endring)
		initring();

	text[LINESIZ] = '\r';
	text[LINESIZ + 1] = '\n';
	for (rs = ring;;) {
		if ((len = endring - rs) >= LINESIZ)
			memmove(text, rs, LINESIZ);
		else {
			memmove(text, rs, len);
			memmove(text + len, ring, LINESIZ - len);
		}
		if (++rs == endring)
			rs = ring;
		if (write(s, text, sizeof(text)) != sizeof(text))
			break;
	}
	exit(0);
}