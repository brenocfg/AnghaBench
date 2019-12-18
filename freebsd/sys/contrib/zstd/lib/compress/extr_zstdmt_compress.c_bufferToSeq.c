#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int capacity; int /*<<< orphan*/ * seq; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ rawSeqStore_t ;
typedef  int /*<<< orphan*/  rawSeq ;
struct TYPE_6__ {int capacity; scalar_t__ start; } ;
typedef  TYPE_2__ buffer_t ;

/* Variables and functions */

__attribute__((used)) static rawSeqStore_t bufferToSeq(buffer_t buffer)
{
    rawSeqStore_t seq = {NULL, 0, 0, 0};
    seq.seq = (rawSeq*)buffer.start;
    seq.capacity = buffer.capacity / sizeof(rawSeq);
    return seq;
}