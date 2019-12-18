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
typedef  int mode_t ;
struct TYPE_2__ {int cmd; int cmd2; int bits; } ;
typedef  TYPE_1__ BITCMD ;

/* Variables and functions */
 int CMD2_CLR ; 
 int CMD2_GBITS ; 
 int CMD2_OBITS ; 
 int CMD2_SET ; 
 int CMD2_UBITS ; 
 int S_IFDIR ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

mode_t
getmode(const void *bbox, mode_t omode)
{
	const BITCMD *set;
	mode_t clrval, newmode, value;

	set = (const BITCMD *)bbox;
	newmode = omode;
	for (value = 0;; set++)
		switch(set->cmd) {
		/*
		 * When copying the user, group or other bits around, we "know"
		 * where the bits are in the mode so that we can do shifts to
		 * copy them around.  If we don't use shifts, it gets real
		 * grundgy with lots of single bit checks and bit sets.
		 */
		case 'u':
			value = (newmode & S_IRWXU) >> 6;
			goto common;

		case 'g':
			value = (newmode & S_IRWXG) >> 3;
			goto common;

		case 'o':
			value = newmode & S_IRWXO;
common:			if (set->cmd2 & CMD2_CLR) {
				clrval =
				    (set->cmd2 & CMD2_SET) ?  S_IRWXO : value;
				if (set->cmd2 & CMD2_UBITS)
					newmode &= ~((clrval<<6) & set->bits);
				if (set->cmd2 & CMD2_GBITS)
					newmode &= ~((clrval<<3) & set->bits);
				if (set->cmd2 & CMD2_OBITS)
					newmode &= ~(clrval & set->bits);
			}
			if (set->cmd2 & CMD2_SET) {
				if (set->cmd2 & CMD2_UBITS)
					newmode |= (value<<6) & set->bits;
				if (set->cmd2 & CMD2_GBITS)
					newmode |= (value<<3) & set->bits;
				if (set->cmd2 & CMD2_OBITS)
					newmode |= value & set->bits;
			}
			break;

		case '+':
			newmode |= set->bits;
			break;

		case '-':
			newmode &= ~set->bits;
			break;

		case 'X':
			if (omode & (S_IFDIR|S_IXUSR|S_IXGRP|S_IXOTH))
				newmode |= set->bits;
			break;

		case '\0':
		default:
#ifdef SETMODE_DEBUG
			(void)printf("getmode:%04o -> %04o\n", omode, newmode);
#endif
			return (newmode);
		}
}