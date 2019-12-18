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
struct winsize {int ws_col; int ws_row; } ;
struct ttysize {int ts_cols; int ts_lines; } ;
typedef  int /*<<< orphan*/  ioctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  SHIN ; 
 int /*<<< orphan*/  TIOCGSIZE ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  T_co ; 
 int /*<<< orphan*/  T_li ; 
 int Val (int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
GetSize(int *lins, int *cols)
{
    *cols = Val(T_co);
    *lins = Val(T_li);

#ifdef TIOCGWINSZ
# define KNOWsize
# ifndef lint
    {
	struct winsize ws;	/* from 4.3 */

	if (ioctl(SHIN, TIOCGWINSZ, (ioctl_t) &ws) != -1) {
	    if (ws.ws_col)
		*cols = ws.ws_col;
	    if (ws.ws_row)
		*lins = ws.ws_row;
	}
    }
# endif /* !lint */
#else /* TIOCGWINSZ */
# ifdef TIOCGSIZE
#  define KNOWsize
    {
	struct ttysize ts;	/* from Sun */

	if (ioctl(SHIN, TIOCGSIZE, (ioctl_t) &ts) != -1) {
	    if (ts.ts_cols)
		*cols = ts.ts_cols;
	    if (ts.ts_lines)
		*lins = ts.ts_lines;
	}
    }
# endif /* TIOCGSIZE */
#endif /* TIOCGWINSZ */

    return (Val(T_co) != *cols || Val(T_li) != *lins);
}