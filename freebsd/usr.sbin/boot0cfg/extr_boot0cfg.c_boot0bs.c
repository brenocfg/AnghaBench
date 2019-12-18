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
typedef  int u_int8_t ;
struct byte_pattern {int member_0; int member_1; int* member_2; int off; scalar_t__ len; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  id1 ;
typedef  int /*<<< orphan*/  id0 ;

/* Variables and functions */
 int b0_ver ; 
 int /*<<< orphan*/  memcmp (int const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
boot0bs(const u_int8_t *bs)
{
    /* the initial code sequence */
    static u_int8_t id0[] = {0xfc, 0x31, 0xc0, 0x8e, 0xc0, 0x8e, 0xd8,
			     0x8e, 0xd0, 0xbc, 0x00, 0x7c };
    /* the drive id */
    static u_int8_t id1[] = {'D', 'r', 'i', 'v', 'e', ' '};
    static struct byte_pattern patterns[] = {
        {0x0,   sizeof(id0), id0},
        {0x1b2, sizeof(id1), id1},
        {1, 0, NULL},
        {0x0,   sizeof(id0), id0},	/* version with NT support */
        {0x1ae, sizeof(id1), id1},
        {2, 0, NULL},
        {0, 0, NULL},
    };
    struct byte_pattern *p = patterns;

    for (;  p->off || p->len; p++) {
	if (p->len == 0)
	    break;
	if (!memcmp(bs + p->off, p->key, p->len))	/* match */
	    continue;
	while (p->len)	/* skip to next block */
	    p++;
    }
    b0_ver = p->off;	/* XXX ugly side effect */
    return p->off;
}