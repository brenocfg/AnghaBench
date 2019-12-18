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
typedef  scalar_t__ uint64_t ;
struct q_pkt {int dummy; } ;
struct _qs {scalar_t__ buf; } ;

/* Variables and functions */

__attribute__((used)) static inline struct q_pkt *
pkt_at(struct _qs *q, uint64_t ofs)
{
    return (struct q_pkt *)(q->buf + ofs);
}