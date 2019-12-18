#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  seq_num; } ;
typedef  TYPE_1__ SSL3_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_NUM_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 

void SSL3_RECORD_set_seq_num(SSL3_RECORD *r, const unsigned char *seq_num)
{
    memcpy(r->seq_num, seq_num, SEQ_NUM_SIZE);
}