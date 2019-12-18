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
typedef  int uint16_t ;
struct fdc_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ FDBCDR ; 
 int /*<<< orphan*/  fdregwr (struct fdc_data*,scalar_t__,int) ; 

__attribute__((used)) static void
fdbcdr_wr(struct fdc_data *fdc, int iswrite, uint16_t count)
{
	fdregwr(fdc, FDBCDR, (count - 1) & 0xff);
	fdregwr(fdc, FDBCDR + 1,
	    (iswrite ? 0x80 : 0) | (((count - 1) >> 8) & 0x7f));
}