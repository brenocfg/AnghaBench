#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tp_col; scalar_t__ tp_row; } ;
struct TYPE_5__ {scalar_t__ ts_begin; } ;
struct TYPE_7__ {TYPE_2__ t_cursor; TYPE_1__ t_originreg; } ;
typedef  TYPE_3__ teken_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  teken_printf (char*) ; 

__attribute__((used)) static ssize_t
teken_subr_do_cpr(const teken_t *t, unsigned int cmd, char response[16])
{

	switch (cmd) {
	case 5: /* Operating status. */
		strcpy(response, "0n");
		return (2);
	case 6: { /* Cursor position. */
		int len;

		len = snprintf(response, 16, "%u;%uR",
		    (t->t_cursor.tp_row - t->t_originreg.ts_begin) + 1,
		    t->t_cursor.tp_col + 1);

		if (len >= 16)
			return (-1);
		return (len);
	}
	case 15: /* Printer status. */
		strcpy(response, "13n");
		return (3);
	case 25: /* UDK status. */
		strcpy(response, "20n");
		return (3);
	case 26: /* Keyboard status. */
		strcpy(response, "27;1n");
		return (5);
	default:
		teken_printf("Unknown DSR\n");
		return (-1);
	}
}