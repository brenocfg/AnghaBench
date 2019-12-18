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
struct adreq {int adr_error; scalar_t__ adr_datasize; scalar_t__ adr_seq; int /*<<< orphan*/  adr_cmd; int /*<<< orphan*/  adr_byteorder; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIST_BYTEORDER_UNDEFINED ; 
 int /*<<< orphan*/  ADIST_CMD_UNDEFINED ; 

__attribute__((used)) static void
adreq_clear(struct adreq *adreq)
{

	adreq->adr_error = -1;
	adreq->adr_byteorder = ADIST_BYTEORDER_UNDEFINED;
	adreq->adr_cmd = ADIST_CMD_UNDEFINED;
	adreq->adr_seq = 0;
	adreq->adr_datasize = 0;
}