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
struct TYPE_2__ {scalar_t__ wstr; scalar_t__ cstr; } ;
struct bwstring {scalar_t__ len; TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  bwstring_iterator ;

/* Variables and functions */
 int MB_CUR_MAX ; 

__attribute__((used)) static inline bwstring_iterator
bws_end(struct bwstring *bws)
{

	return ((MB_CUR_MAX == 1) ?
	    (bwstring_iterator) (bws->data.cstr + bws->len) :
	    (bwstring_iterator) (bws->data.wstr + bws->len));
}