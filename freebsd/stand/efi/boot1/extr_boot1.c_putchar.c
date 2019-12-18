#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ConOut; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* OutputString ) (TYPE_1__*,char*) ;} ;
typedef  char CHAR16 ;

/* Variables and functions */
 TYPE_3__* ST ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*) ; 

void
putchar(int c)
{
	CHAR16 buf[2];

	if (c == '\n') {
		buf[0] = '\r';
		buf[1] = 0;
		ST->ConOut->OutputString(ST->ConOut, buf);
	}
	buf[0] = c;
	buf[1] = 0;
	ST->ConOut->OutputString(ST->ConOut, buf);
}