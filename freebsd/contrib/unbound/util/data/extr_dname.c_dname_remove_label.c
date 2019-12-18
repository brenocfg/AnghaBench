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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  LABEL_IS_PTR (size_t) ; 
 int /*<<< orphan*/  log_assert (int) ; 

void 
dname_remove_label(uint8_t** dname, size_t* len)
{
	size_t lablen;
	log_assert(dname && *dname && len);
	lablen = (*dname)[0];
	log_assert(!LABEL_IS_PTR(lablen));
	log_assert(*len > lablen);
	if(lablen == 0)
		return; /* do not modify root label */
	*len -= lablen+1;
	*dname += lablen+1;
}