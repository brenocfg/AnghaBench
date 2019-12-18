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
struct tty {int t_column; int t_writepos; int /*<<< orphan*/  t_inq; int /*<<< orphan*/  t_outq; } ;

/* Variables and functions */
#define  CCR 132 
#define  CEOF 131 
#define  CERASE2 130 
 int CMP_FLAG (int /*<<< orphan*/ ,int) ; 
#define  CNL 129 
#define  CTAB 128 
 int CTL_VALID (char) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int OCRNL ; 
 int ONLCR ; 
 int ONLRET ; 
 int ONOCR ; 
 int ONOEOT ; 
 int OPOST ; 
 int PRINT_NORMAL () ; 
 int TAB3 ; 
 int /*<<< orphan*/  o ; 
 int /*<<< orphan*/  ttyinq_reprintpos_set (int /*<<< orphan*/ *) ; 
 unsigned int ttyoutq_write_nofrag (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
ttydisc_write_oproc(struct tty *tp, char c)
{
	unsigned int scnt, error;

	MPASS(CMP_FLAG(o, OPOST));
	MPASS(CTL_VALID(c));

#define PRINT_NORMAL() ttyoutq_write_nofrag(&tp->t_outq, &c, 1)
	switch (c) {
	case CEOF:
		/* End-of-text dropping. */
		if (CMP_FLAG(o, ONOEOT))
			return (0);
		return PRINT_NORMAL();

	case CERASE2:
		/* Handle backspace to fix tab expansion. */
		if (PRINT_NORMAL() != 0)
			return (-1);
		if (tp->t_column > 0)
			tp->t_column--;
		return (0);

	case CTAB:
		/* Tab expansion. */
		scnt = 8 - (tp->t_column & 7);
		if (CMP_FLAG(o, TAB3)) {
			error = ttyoutq_write_nofrag(&tp->t_outq,
			    "        ", scnt);
		} else {
			error = PRINT_NORMAL();
		}
		if (error)
			return (-1);

		tp->t_column += scnt;
		MPASS((tp->t_column % 8) == 0);
		return (0);

	case CNL:
		/* Newline conversion. */
		if (CMP_FLAG(o, ONLCR)) {
			/* Convert \n to \r\n. */
			error = ttyoutq_write_nofrag(&tp->t_outq, "\r\n", 2);
		} else {
			error = PRINT_NORMAL();
		}
		if (error)
			return (-1);

		if (CMP_FLAG(o, ONLCR|ONLRET)) {
			tp->t_column = tp->t_writepos = 0;
			ttyinq_reprintpos_set(&tp->t_inq);
		}
		return (0);

	case CCR:
		/* Carriage return to newline conversion. */
		if (CMP_FLAG(o, OCRNL))
			c = CNL;
		/* Omit carriage returns on column 0. */
		if (CMP_FLAG(o, ONOCR) && tp->t_column == 0)
			return (0);
		if (PRINT_NORMAL() != 0)
			return (-1);

		tp->t_column = tp->t_writepos = 0;
		ttyinq_reprintpos_set(&tp->t_inq);
		return (0);
	}

	/*
	 * Invisible control character. Print it, but don't
	 * increase the column count.
	 */
	return PRINT_NORMAL();
#undef PRINT_NORMAL
}