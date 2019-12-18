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
struct termios {int c_cflag; } ;

/* Variables and functions */
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int PARENB ; 

__attribute__((used)) static int
bits_per_char(struct termios *t)
{
	int bits;

	bits = 1;		/* start bit */
	switch (t->c_cflag & CSIZE) {
	case CS5:	bits += 5;	break;
	case CS6:	bits += 6;	break;
	case CS7:	bits += 7;	break;
	case CS8:	bits += 8;	break;
	}
	bits++;			/* stop bit */
	if (t->c_cflag & PARENB)
		bits++;
	if (t->c_cflag & CSTOPB)
		bits++;
	return (bits);
}