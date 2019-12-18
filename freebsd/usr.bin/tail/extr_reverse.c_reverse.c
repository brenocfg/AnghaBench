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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ off_t ;
typedef  enum STYLE { ____Placeholder_STYLE } STYLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  FBYTES 132 
#define  FLINES 131 
#define  RBYTES 130 
#define  REVERSE 129 
#define  RLINES 128 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytes (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  lines (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  r_buf (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_reg (int /*<<< orphan*/ *,char const*,int,scalar_t__,struct stat*) ; 

void
reverse(FILE *fp, const char *fn, enum STYLE style, off_t off, struct stat *sbp)
{
	if (style != REVERSE && off == 0)
		return;

	if (S_ISREG(sbp->st_mode))
		r_reg(fp, fn, style, off, sbp);
	else
		switch(style) {
		case FBYTES:
		case RBYTES:
			bytes(fp, fn, off);
			break;
		case FLINES:
		case RLINES:
			lines(fp, fn, off);
			break;
		case REVERSE:
			r_buf(fp, fn);
			break;
		default:
			break;
		}
}