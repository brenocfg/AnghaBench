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
struct TYPE_2__ {char* cstr; int* wstr; } ;
struct bwstring {size_t len; TYPE_1__ data; } ;

/* Variables and functions */
 int MB_CUR_MAX ; 

void
bws_setlen(struct bwstring *bws, size_t newlen)
{

	if (bws && newlen != bws->len && newlen <= bws->len) {
		bws->len = newlen;
		if (MB_CUR_MAX == 1)
			bws->data.cstr[newlen] = '\0';
		else
			bws->data.wstr[newlen] = L'\0';
	}
}