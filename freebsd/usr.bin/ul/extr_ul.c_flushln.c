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
struct TYPE_2__ {int c_mode; char c_char; int c_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURS_RIGHT ; 
 int NORMAL ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iattr () ; 
 scalar_t__ iflag ; 
 int /*<<< orphan*/  initbuf () ; 
 int maxcol ; 
 scalar_t__ must_overstrike ; 
 TYPE_1__* obuf ; 
 int /*<<< orphan*/  outc (char,int) ; 
 int /*<<< orphan*/  overstrike () ; 
 int /*<<< orphan*/  putwchar (char) ; 
 int /*<<< orphan*/  setnewmode (int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ upln ; 

__attribute__((used)) static void
flushln(void)
{
	int lastmode;
	int i;
	int hadmodes = 0;

	lastmode = NORMAL;
	for (i = 0; i < maxcol; i++) {
		if (obuf[i].c_mode != lastmode) {
			hadmodes++;
			setnewmode(obuf[i].c_mode);
			lastmode = obuf[i].c_mode;
		}
		if (obuf[i].c_char == '\0') {
			if (upln)
				PRINT(CURS_RIGHT);
			else
				outc(' ', 1);
		} else
			outc(obuf[i].c_char, obuf[i].c_width);
		if (obuf[i].c_width > 1)
			i += obuf[i].c_width - 1;
	}
	if (lastmode != NORMAL) {
		setnewmode(0);
	}
	if (must_overstrike && hadmodes)
		overstrike();
	putwchar('\n');
	if (iflag && hadmodes)
		iattr();
	(void)fflush(stdout);
	if (upln)
		upln--;
	initbuf();
}