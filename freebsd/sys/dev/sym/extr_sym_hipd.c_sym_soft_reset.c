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
typedef  int u_char ;
typedef  int /*<<< orphan*/  hcb_p ;

/* Variables and functions */
 int /*<<< orphan*/  CABRT ; 
 int DIP ; 
 int INB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SIP ; 
 int /*<<< orphan*/  nc_dstat ; 
 int /*<<< orphan*/  nc_istat ; 
 int /*<<< orphan*/  nc_sist ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sym_chip_reset (int /*<<< orphan*/ ) ; 
 char* sym_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_soft_reset (hcb_p np)
{
	u_char istat;
	int i;

	OUTB (nc_istat, CABRT);
	for (i = 1000000 ; i ; --i) {
		istat = INB (nc_istat);
		if (istat & SIP) {
			INW (nc_sist);
			continue;
		}
		if (istat & DIP) {
			OUTB (nc_istat, 0);
			INB (nc_dstat);
			break;
		}
	}
	if (!i)
		printf("%s: unable to abort current chip operation.\n",
			sym_name(np));
	sym_chip_reset (np);
}