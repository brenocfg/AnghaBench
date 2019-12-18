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
typedef  scalar_t__ uint32_t ;
struct nm_pcap_file {char* cur; char const* lim; int err; int /*<<< orphan*/  swap; } ;

/* Variables and functions */
 scalar_t__ cvt (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
read_next_info(struct nm_pcap_file *pf, int size)
{
    const char *end = pf->cur + size;
    uint32_t ret;
    if (end > pf->lim) {
	pf->err = 1;
	ret = 0;
    } else {
	ret = cvt(pf->cur, size, pf->swap);
	pf->cur = end;
    }
    return ret;
}